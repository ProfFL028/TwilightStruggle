package com.proffl.flink.operator

import com.proffl.flink.model.Keyed
import com.proffl.flink.model.KeysExtractor
import com.proffl.flink.model.Rule
import com.proffl.flink.model.Transaction
import org.apache.flink.configuration.Configuration
import org.apache.flink.metrics.Gauge
import org.apache.flink.streaming.api.functions.co.BroadcastProcessFunction
import org.apache.flink.streaming.api.functions.co.CoProcessFunction
import org.apache.flink.util.Collector
import org.slf4j.Logger
import org.slf4j.LoggerFactory


class DynamicKeyFunction : BroadcastProcessFunction<Transaction, Rule, Keyed<Transaction, String, Integer>>() {
    companion object {
        private val log = LoggerFactory.getLogger(DynamicKeyFunction::class.java)
    }

    private lateinit var ruleCounterGauge: RuleCounterGauge

    override fun open(parameters: Configuration?) {
        super.open(parameters)
        this.ruleCounterGauge = RuleCounterGauge(0)
        runtimeContext.metricGroup.gauge("numberOfActiveRules", ruleCounterGauge)
    }

    override fun processElement(
        value: Transaction,
        ctx: ReadOnlyContext,
        out: Collector<Keyed<Transaction, String, Integer>>
    ) {
        var ruleState = ctx.getBroadcastState(Rule.ruleDescriptor)

        var ruleCounter = 0
        for (entry in ruleState.immutableEntries()) {
            val rule = entry.value
            out.collect(
                Keyed(value, KeysExtractor.getKey(rule.groupingKeyNames, value), Integer(rule.ruleId))
            )
            ruleCounter++
        }
        ruleCounterGauge.value = ruleCounter
    }

    override fun processBroadcastElement(
        value: Rule,
        ctx: Context,
        out: Collector<Keyed<Transaction, String, Integer>>
    ) {
        log.trace("Processing $value")
        val broadcastState = ctx.getBroadcastState(Rule.ruleDescriptor)

        when (value.ruleState) {
            Rule.RuleState.ACTIVE, Rule.RuleState.PAUSE -> broadcastState.put(Integer(value.ruleId), value)
            Rule.RuleState.DELETE -> broadcastState.remove(Integer(value.ruleId))
            Rule.RuleState.CONTROL -> {
                if (value.controlType == Rule.ControlType.DELETE_RULES_ALL) {
                    val it = broadcastState.iterator()
                    while (it.hasNext()) {
                        val ruleEntry = it.next()
                        broadcastState.remove(ruleEntry.key)
                        log.trace("Remove ${ruleEntry.value}")
                    }
                }
            }
        }
    }

    data class RuleCounterGauge(var value: Int): Gauge<Integer> {
        override fun getValue(): Integer {
            return Integer(value)
        }

    }
}


