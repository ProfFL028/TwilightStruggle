package com.proffl.flink.connector

import com.proffl.flink.model.InputMessage
import com.proffl.flink.schema.InputMessageDeserializationSchema
import org.apache.flink.api.common.serialization.SimpleStringSchema
import org.apache.flink.streaming.connectors.kafka.FlinkKafkaConsumer
import java.util.*

object Consumer {
    fun createStringConsumerForTopic(
        topic: String?,
        kafkaAddress: String?,
        kafkaGroup: String?
    ): FlinkKafkaConsumer<String> {
        val props = Properties()
        props.setProperty("bootstrap.servers", kafkaAddress)
        props.setProperty("group.id", kafkaGroup)
        return FlinkKafkaConsumer(topic, SimpleStringSchema(), props)
    }

    fun createInputMessageConsumer(
        topic: String?,
        kafkaAddress: String?,
        kafkaGroup: String?
    ): FlinkKafkaConsumer<InputMessage> {
        val properties = Properties()
        properties.setProperty("bootstrap.servers", kafkaAddress)
        properties.setProperty("group.id", kafkaGroup)
        return FlinkKafkaConsumer<InputMessage>(topic, InputMessageDeserializationSchema(), properties)
    }
}
