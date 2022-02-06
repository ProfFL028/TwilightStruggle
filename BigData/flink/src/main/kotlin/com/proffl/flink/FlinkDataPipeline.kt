package com.proffl.flink

import com.proffl.flink.connector.Consumer.createInputMessageConsumer
import com.proffl.flink.connector.Producer.Companion.createBackupProducer
import com.proffl.flink.operator.BackupAggregator
import com.proffl.flink.operator.InputMessageTimestampAssigner
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import org.apache.flink.streaming.api.windowing.time.Time

class FlinkDataPipeline {
    companion object {
        fun createBackup() {
            var inputTopic = "flink-input"
            var outputTopic = "flink-output"
            var consumerGroup = "proffl"
            var kafkaAddress = "192.168.6.203:9092"

            var environment = StreamExecutionEnvironment.getExecutionEnvironment()
            // environment.streamTimeCharacteristic(TimeCharacteristic.EventTime) //default EventTime since 1.12
            var flinkKafkaConsumer = createInputMessageConsumer(inputTopic, kafkaAddress, consumerGroup)
            flinkKafkaConsumer.setStartFromEarliest()

            flinkKafkaConsumer.assignTimestampsAndWatermarks(InputMessageTimestampAssigner())
            var flinkKafkaProducer = createBackupProducer(outputTopic, kafkaAddress)

            var inputMessageStream = environment.addSource(flinkKafkaConsumer)
            inputMessageStream.timeWindowAll(Time.hours(24)).aggregate(BackupAggregator()).addSink(flinkKafkaProducer)
            environment.execute()
        }

    }
}

fun main(args: Array<String>) {
    FlinkDataPipeline.createBackup()
}
