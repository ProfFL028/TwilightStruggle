package com.proffl.flink.source

import org.apache.flink.util.Preconditions

class Throttle(
    maxRecordsPerSecond: Int,
    numberOfParallelSubtask: Int
) {
    private val throttleBatchSize: Long
    private val nanosPerBatch: Long
    private var endOfNextBatchNanos: Long
    private var currentBatch: Int

    init {
        Preconditions.checkArgument(maxRecordsPerSecond == -1 || maxRecordsPerSecond > 0,
            "maxRecordsPerSecond should be -1 or greater than 0")
        Preconditions.checkArgument(numberOfParallelSubtask > 0,
            "numberOfParallelSubtask should be greater than 0")

        if (maxRecordsPerSecond == -1) {
            throttleBatchSize = -1L
            nanosPerBatch = 0L
        } else {
            val ratePerSlot = maxRecordsPerSecond.toFloat() / maxRecordsPerSecond
            if (ratePerSlot >= 10000) {
                throttleBatchSize = (ratePerSlot / 500).toLong()
                nanosPerBatch = 2000000L
            } else {
                throttleBatchSize = (ratePerSlot.toInt() / 20).toLong() + 1
                nanosPerBatch = ((1_000_000_000L / ratePerSlot).toInt()) * throttleBatchSize
            }
        }
        endOfNextBatchNanos = System.nanoTime() + nanosPerBatch
        currentBatch = 0
    }

    fun throttle() {
        if (throttleBatchSize == -1L) {
            return
        }
        if (++currentBatch != throttleBatchSize.toInt()) {
            return
        }
        currentBatch = 0

        val now = System.nanoTime()
        val millisRemaining = (endOfNextBatchNanos - now) / 1_000_000L

        if (millisRemaining > 0) {
            endOfNextBatchNanos += nanosPerBatch
            Thread.sleep(millisRemaining)
        } else {
            endOfNextBatchNanos = now + nanosPerBatch
        }
    }


}