package com.proffl.flink.operator.agg

import org.apache.flink.api.common.accumulators.Accumulator
import org.apache.flink.api.common.accumulators.SimpleAccumulator
import java.math.BigDecimal
import java.math.RoundingMode

class AverageAccumulator(var count: Long = 0L, var sum: BigDecimal = BigDecimal.ZERO) : SimpleAccumulator<BigDecimal> {

    override fun clone(): Accumulator<BigDecimal, BigDecimal> {
        return AverageAccumulator(count, sum)
    }

    override fun add(value: BigDecimal) {
        count++
        sum += value
    }

    override fun getLocalValue(): BigDecimal {
        if (this.count == 0L) {
            return BigDecimal.ZERO
        }
        return sum.divide(BigDecimal(count), RoundingMode.HALF_UP)
    }

    override fun resetLocal() {
        this.count = 0
        this.sum = BigDecimal.ZERO
    }

    override fun merge(other: Accumulator<BigDecimal, BigDecimal>) {
        if (other is AverageAccumulator) {
            val otherAv = other as AverageAccumulator
            this.count += otherAv.count
            this.sum += otherAv.sum
        } else {
            throw RuntimeException("Invalid input type: $other")
        }
    }

    override fun toString(): String {
        return "AverageAccumulator: $sum in all $count elements"
    }
}