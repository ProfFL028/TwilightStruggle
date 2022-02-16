package com.proffl.flink.model

interface TimestampAssignable<T> {
    fun assignIngestionTimestamp(timestamp: T)
}