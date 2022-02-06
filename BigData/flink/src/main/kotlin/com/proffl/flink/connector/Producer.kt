package com.proffl.flink.connector

import com.proffl.flink.model.Backup
import com.proffl.flink.schema.BackupSerializationSchema
import org.apache.flink.api.common.serialization.SimpleStringSchema
import org.apache.flink.streaming.connectors.kafka.FlinkKafkaProducer
import org.apache.flink.streaming.connectors.kafka.FlinkKafkaProducer011


class Producer {
    companion object {
        fun createStringProducer(topic: String?, kafkaAddress: String?): FlinkKafkaProducer<String> {
            return FlinkKafkaProducer(kafkaAddress, topic, SimpleStringSchema())
        }

        fun createBackupProducer(topic: String?, kafkaAddress: String?): FlinkKafkaProducer<Backup> {
            return FlinkKafkaProducer(kafkaAddress, topic, BackupSerializationSchema())
        }
    }
}
