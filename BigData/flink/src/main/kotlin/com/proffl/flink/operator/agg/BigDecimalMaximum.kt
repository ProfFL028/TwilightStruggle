package com.proffl.flink.operator.agg

import org.apache.flink.api.common.accumulators.Accumulator
import org.apache.flink.api.common.accumulators.SimpleAccumulator
import java.math.BigDecimal

class BigDecimalMaximum(var max: BigDecimal = BigDecimal(Double.MIN_VALUE)) : SimpleAccumulator<BigDecimal> {
    override fun clone(): Accumulator<BigDecimal, BigDecimal> {
        return BigDecimalMaximum(max)
    }

    override fun add(value: BigDecimal) {
        if (value > max) {
            max = value
        }
    }

    override fun getLocalValue(): BigDecimal {
        return max
    }

    override fun resetLocal() {
        max = BigDecimal(Double.MIN_VALUE)
    }

    override fun merge(other: Accumulator<BigDecimal, BigDecimal>) {
        max = max.max(other.localValue)
    }
}