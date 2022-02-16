package com.proffl.flink.config

import com.proffl.flink.config.Parameters.Companion.KAFKA_HOST
import com.proffl.flink.config.Parameters.Companion.KAFKA_PORT
import com.proffl.flink.config.Parameters.Companion.OFFSET
import java.util.*

class KafkaUtils {
    companion object {
        fun initConsumerProperties(config: Config): Properties {
            val kafkaProps: Properties = initProperties(config)
            val offset = config.get(OFFSET)
            kafkaProps.setProperty("auto.offset.reset", offset)
            return kafkaProps
        }

        fun initProducerProperties(params: Config): Properties? {
            return initProperties(params)
        }

        private fun initProperties(config: Config): Properties {
            val kafkaProps = Properties()
            val kafkaHost = config.get(KAFKA_HOST)
            val kafkaPort = config.get(KAFKA_PORT)
            val servers = String.format("%s:%s", kafkaHost, kafkaPort)
            kafkaProps.setProperty("bootstrap.servers", servers)
            return kafkaProps
        }
    }
}