package com.proffl.flink.operator.agg

import org.apache.flink.api.common.accumulators.Accumulator
import org.apache.flink.api.common.accumulators.SimpleAccumulator
import java.math.BigDecimal

class BigDecimalMinimum(var min: BigDecimal = BigDecimal(Double.MAX_VALUE)) : SimpleAccumulator<BigDecimal> {
    override fun clone(): Accumulator<BigDecimal, BigDecimal> {
        return BigDecimalMinimum(min)
    }

    override fun add(value: BigDecimal) {
        min = min.min(value)
    }

    override fun getLocalValue(): BigDecimal {
        return min
    }

    override fun resetLocal() {
        min = BigDecimal(Double.MAX_VALUE)
    }

    override fun merge(other: Accumulator<BigDecimal, BigDecimal>) {
        min = min.min(other.localValue)
    }

}