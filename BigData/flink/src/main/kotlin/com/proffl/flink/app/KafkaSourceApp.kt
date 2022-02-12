package com.proffl.flink.app

import org.apache.flink.api.common.eventtime.WatermarkStrategy
import org.apache.flink.api.common.serialization.SimpleStringSchema
import org.apache.flink.connector.kafka.source.KafkaSource
import org.apache.flink.connector.kafka.source.enumerator.initializer.OffsetsInitializer
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment

fun main() {
    var env = StreamExecutionEnvironment.getExecutionEnvironment()
    var kafkaSource =KafkaSource.builder<String>().
    setBootstrapServers("localhost:9092")
        .setGroupId("proffl")
        .setStartingOffsets(OffsetsInitializer.earliest())
        .setTopics("flink-input")
        .setValueOnlyDeserializer(SimpleStringSchema())
        .build()

     var kafkaStream = env.fromSource(kafkaSource,
        WatermarkStrategy.noWatermarks(),
        "kafka_string")
    kafkaStream.print()

    env.execute()
}