package com.proffl.flink.operator.agg

import org.apache.flink.annotation.PublicEvolving
import org.apache.flink.api.common.accumulators.Accumulator
import org.apache.flink.api.common.accumulators.SimpleAccumulator
import java.math.BigDecimal

@PublicEvolving
class BigDecimalCounter(value: BigDecimal=BigDecimal.ZERO) : SimpleAccumulator<BigDecimal> {
    private var localValue:BigDecimal = BigDecimal.ZERO
    init {
        localValue = value
    }
    override fun clone(): Accumulator<BigDecimal, BigDecimal> {
        return BigDecimalCounter(localValue)
    }

    override fun add(value: BigDecimal) {
        localValue = localValue.add(value)
    }


    override fun resetLocal() {
        localValue = BigDecimal.ZERO
    }

    override fun merge(other: Accumulator<BigDecimal, BigDecimal>) {
        localValue = localValue.add(other.localValue)
    }

    override fun getLocalValue(): BigDecimal {
        return localValue
    }

}