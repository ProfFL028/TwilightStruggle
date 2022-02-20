package com.proffl.flink.model

import com.proffl.flink.operator.agg.AverageAccumulator
import com.proffl.flink.operator.agg.BigDecimalCounter
import com.proffl.flink.operator.agg.BigDecimalMaximum
import com.proffl.flink.operator.agg.BigDecimalMinimum
import org.apache.flink.api.common.accumulators.SimpleAccumulator
import org.apache.flink.api.common.state.MapStateDescriptor
import org.apache.flink.api.common.time.Time
import org.apache.flink.api.common.typeinfo.TypeInformation
import org.apache.flink.api.common.typeinfo.Types
import org.apache.flink.util.OutputTag
import java.math.BigDecimal

data class Rule(
    var ruleId: Int = 0,
    var ruleState: RuleState = RuleState.PAUSE,
    var groupingKeyNames: List<String> = ArrayList(),
    var aggregateFieldName: String = "",
    var aggregatorFunctionType: AggregatorFunctionType = AggregatorFunctionType.AVG,
    var limitOperatorType: LimitOperatorType = LimitOperatorType.LESS,
    var limit: BigDecimal = BigDecimal(0),
    var windowMinutes: Long = 0L,
    var controlType: ControlType = ControlType.CLEAR_STATE_ALL
) {
    val windowMillis: Long
        get() {
            return Time.minutes(windowMinutes).toMilliseconds()
        }

    fun apply(comparisonValue: BigDecimal): Boolean {
        return when (limitOperatorType) {
            LimitOperatorType.EQUAL -> comparisonValue.compareTo(limit) == 0
            LimitOperatorType.NOT_EQUAL -> comparisonValue.compareTo(limit) != 0
            LimitOperatorType.GREATER -> comparisonValue > limit
            LimitOperatorType.LESS -> comparisonValue < limit
            LimitOperatorType.LESS_EQUAL -> comparisonValue <= limit
            LimitOperatorType.GREATER_EQUAL -> comparisonValue >= limit
        }
    }

    fun getWindowStartFor(timestamp: Long): Long {
        return (timestamp - windowMillis)
    }

    enum class AggregatorFunctionType {
        SUM, AVG, MIN, MAX
    }

    enum class LimitOperatorType(val operator: String) {
        EQUAL("="),
        NOT_EQUAL("!="),
        GREATER_EQUAL(">="),
        LESS_EQUAL("<="),
        GREATER(">"),
        LESS("<");
    }

    enum class RuleState {
        ACTIVE, PAUSE, DELETE, CONTROL
    }

    enum class ControlType {
        CLEAR_STATE_ALL, DELETE_RULES_ALL, EXPORT_RULES_CURRENT
    }

    companion object {
        val ruleDescriptor =
            MapStateDescriptor("rules", TypeInformation.of(Integer::class.java), TypeInformation.of(Rule::class.java))

        val latencySinkTag = OutputTag<Long>("latency-sink", Types.LONG)
        val currentRulesSinkTag = OutputTag<Rule>("current-rules-sink", TypeInformation.of(Rule::class.java))
    }
}

class RuleHelper {
    companion object {
        fun getAggregator(rule: Rule): SimpleAccumulator<BigDecimal> {
            return when (rule.aggregatorFunctionType) {
                Rule.AggregatorFunctionType.SUM -> BigDecimalCounter()
                Rule.AggregatorFunctionType.AVG -> AverageAccumulator()
                Rule.AggregatorFunctionType.MAX -> BigDecimalMaximum()
                Rule.AggregatorFunctionType.MIN -> BigDecimalMinimum()
            }
        }
    }
}