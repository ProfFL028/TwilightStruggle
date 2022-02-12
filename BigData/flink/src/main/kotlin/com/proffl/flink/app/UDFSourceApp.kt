package com.proffl.flink.app

import com.proffl.flink.source.SensorSource
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment

fun main() {
    var env = StreamExecutionEnvironment.getExecutionEnvironment()

    var sensorStream = env.addSource(SensorSource())

    sensorStream.print()

    env.execute()
}