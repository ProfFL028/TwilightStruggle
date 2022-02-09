package com.proffl.flink

import com.proffl.flink.connector.Consumer.createStringConsumerForTopic
import com.proffl.flink.connector.Producer.Companion.createStringProducer
import org.apache.flink.api.common.functions.MapFunction
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import java.util.*

class StringCapitalizer : MapFunction<String, String> {
    @Throws(Exception::class)
    override fun map(data: String): String {
        return data.uppercase(Locale.getDefault())
    }
}
class FlinkDataPipeline {
    companion object {
        fun createBackup() {
            var inputTopic = "flink-input"
            var outputTopic = "flink-output"
            var consumerGroup = "proffl"
            var kafkaAddress = "localhost:9092"

            var environment = StreamExecutionEnvironment.getExecutionEnvironment()
            // environment.streamTimeCharacteristic(TimeCharacteristic.EventTime) //default EventTime since 1.12
            var flinkKafkaConsumer = createStringConsumerForTopic(inputTopic, kafkaAddress, consumerGroup)
            flinkKafkaConsumer.setStartFromEarliest()

            var flinkKafkaProducer = createStringProducer(outputTopic, kafkaAddress)

            var inputMessageStream = environment.addSource(flinkKafkaConsumer)
            inputMessageStream.map(StringCapitalizer()).addSink(flinkKafkaProducer)
            environment.execute()
        }

    }
}

fun main(args: Array<String>) {
    FlinkDataPipeline.createBackup()
}
