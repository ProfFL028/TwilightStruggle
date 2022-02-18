package com.proffl.flink.times

import com.proffl.flink.model.TimestampAssignable
import org.apache.flink.api.common.functions.RichFlatMapFunction
import org.apache.flink.util.Collector

class TimeStamper<T: TimestampAssignable<Long>>: RichFlatMapFunction<T, T>() {
    override fun flatMap(value: T, out: Collector<T>) {
        value.assignIngestionTimestamp(System.currentTimeMillis())
        out.collect(value)
    }
}