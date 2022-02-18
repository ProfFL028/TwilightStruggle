package com.proffl.flink.times

import com.proffl.flink.model.Transaction
import org.apache.flink.streaming.api.functions.timestamps.BoundedOutOfOrdernessTimestampExtractor
import org.apache.flink.streaming.api.windowing.time.Time
import java.util.concurrent.TimeUnit

class SimpleBoundedOutOfOrdernessTimestampExtractor<T: Transaction>(
    outOfOrdernessMillis: Long
): BoundedOutOfOrdernessTimestampExtractor<T>(Time.of(outOfOrdernessMillis, TimeUnit.MILLISECONDS)) {
    override fun extractTimestamp(element: T): Long {
        return element.eventTime
    }


}