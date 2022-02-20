package com.proffl.flink.operator

import com.proffl.flink.model.*
import org.apache.flink.api.common.state.MapState
import org.apache.flink.api.common.state.MapStateDescriptor
import org.apache.flink.api.common.typeinfo.BasicTypeInfo
import org.apache.flink.api.common.typeinfo.TypeHint
import org.apache.flink.api.common.typeinfo.TypeInformation
import org.apache.flink.configuration.Configuration
import org.apache.flink.metrics.Meter
import org.apache.flink.metrics.MeterView
import org.apache.flink.streaming.api.functions.co.KeyedBroadcastProcessFunction
import org.apache.flink.util.Collector
import org.slf4j.LoggerFactory
import java.math.BigDecimal
import java.util.*

class DynamicAlertFunction :
    KeyedBroadcastProcessFunction<String, Keyed<Transaction, String, Integer>, Rule, Alert<Transaction, BigDecimal>>() {

    companion object {
        private const val COUNT = "COUNT_FLINK"
        private const val COUNT_WITH_RESET = "COUNT_WITH_RESET_FLINK"

        private const val WIDEST_RULE_KEY = Int.MIN_VALUE

        private val logger = LoggerFactory.getLogger(DynamicAlertFunction::class.java)
    }

    @Transient
    private lateinit var windowState: MapState<Long, MutableSet<Transaction>>
    private lateinit var alertMeter: Meter

    private var windowStateDescriptor = MapStateDescriptor(
        "windowState", BasicTypeInfo.LONG_TYPE_INFO,
        TypeInformation.of(TransactionMutableSetTypeInt())
    )

    class TransactionMutableSetTypeInt : TypeHint<MutableSet<Transaction>>()

    override fun open(parameters: Configuration?) {
        super.open(parameters)
        windowState = runtimeContext.getMapState(windowStateDescriptor)
        alertMeter = MeterView(60)
        runtimeContext.metricGroup.meter("alertsPerSecond", alertMeter)
    }

    override fun processElement(
        value: Keyed<Transaction, String, Integer>,
        ctx: ReadOnlyContext,
        out: Collector<Alert<Transaction, BigDecimal>>
    ) {
        val currentEventTime = value.wrapped!!.eventTime

        if (!windowState.contains(currentEventTime)) {
            windowState.put(currentEventTime, HashSet())
        }
        windowState[currentEventTime].add(value.wrapped!!)

        val ingestionTime = value.wrapped!!.ingestionTimestamp
        ctx.output(Rule.latencySinkTag, System.currentTimeMillis() - ingestionTime)

        if (!ctx.getBroadcastState(Rule.ruleDescriptor).contains(value.id)) {
            return
        }
        val rule = ctx.getBroadcastState(Rule.ruleDescriptor).get(value.id)
        if (rule.ruleState == Rule.RuleState.ACTIVE) {
            val windowStartForEvent = rule.getWindowStartFor(currentEventTime)

            val cleanupTime = (currentEventTime / 1000) * 1000
            ctx.timerService().registerEventTimeTimer(cleanupTime)

            val aggregator = RuleHelper.getAggregator(rule)
            for (stateEventTime in windowState.keys()) {
                if (stateEventTime in windowStartForEvent..currentEventTime) {
                    val inWindow = windowState.get(stateEventTime)
                    if (COUNT == rule.aggregateFieldName || COUNT_WITH_RESET == rule.aggregateFieldName) {
                        for (event in inWindow) {
                            aggregator.add(BigDecimal.ONE)
                        }
                    } else {
                        for (event in inWindow) {
                            val aggValue = FieldsExtractor.getBigDecimalByName(event, rule.aggregateFieldName)
                            aggregator.add(aggValue)
                        }
                    }
                }
            }
            val aggResult = aggregator.localValue
            val ruleResult = rule.apply(aggResult)
            logger.trace("Rule ${rule.ruleId} | ${value.key} : $aggResult -> $ruleResult")

            if (ruleResult) {
                if (COUNT_WITH_RESET == rule.aggregateFieldName) {
                    val it = windowState.keys().iterator()
                    while (it.hasNext()) {
                        it.next()
                        it.remove()
                    }
                }
                alertMeter.markEvent()
                out.collect(Alert(Integer(rule.ruleId), rule, value.key!!, value.wrapped, aggResult))
            }
        }
    }

    override fun processBroadcastElement(value: Rule, ctx: Context, out: Collector<Alert<Transaction, BigDecimal>>) {
        logger.trace("Processing $value")
        val broadcastState = ctx.getBroadcastState(Rule.ruleDescriptor)
        when (value.ruleState) {
            Rule.RuleState.ACTIVE, Rule.RuleState.PAUSE -> broadcastState.put(Integer(value.ruleId), value)
            Rule.RuleState.DELETE -> broadcastState.remove(Integer(value.ruleId))
            else -> {}
        }
        val widestWindow = broadcastState.get(Integer(WIDEST_RULE_KEY))
        if (widestWindow != null && widestWindow.ruleState == Rule.RuleState.ACTIVE) {
            broadcastState.put(Integer(WIDEST_RULE_KEY), value)
        }
    }

    override fun onTimer(timestamp: Long, ctx: OnTimerContext, out: Collector<Alert<Transaction, BigDecimal>>) {
        val widestWindowRule = ctx.getBroadcastState(Rule.ruleDescriptor).get(Integer(WIDEST_RULE_KEY))
        val cleanupEventTimeWindow = Optional.ofNullable(widestWindowRule).map(Rule::windowMillis)
        val cleanupEventTimeThreshold = cleanupEventTimeWindow.map { window -> timestamp - window }
        cleanupEventTimeThreshold.ifPresent(this::evictAgedElementsFromWindow)
    }

    private fun evictAgedElementsFromWindow(threshold: Long) {
        try {
            val keys = windowState.keys().iterator()
            while (keys.hasNext()) {
                val stateEventTime = keys.next()
                if (stateEventTime < threshold) {
                    keys.remove()
                }
            }
        } catch (ex: Exception) {
            throw RuntimeException(ex)
        }
    }
}