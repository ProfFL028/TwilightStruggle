package me.proffl.util

import org.apache.kafka.clients.consumer.ConsumerConfig
import org.apache.kafka.common.serialization.Serdes
import org.apache.kafka.streams.StreamsConfig
import java.util.*

class KafkaUtil {
    companion object {
        fun getDefaultConfig(
            id: String = "dev1",
            servers: String = "localhost:29092",
            offset: String = "earliest"
        ): Properties {
            val config = Properties()
            config[StreamsConfig.APPLICATION_ID_CONFIG] = id
            config[StreamsConfig.BOOTSTRAP_SERVERS_CONFIG] = servers
            config[ConsumerConfig.AUTO_OFFSET_RESET_CONFIG] = offset
            config[StreamsConfig.DEFAULT_KEY_SERDE_CLASS_CONFIG] = Serdes.Void().javaClass
            config[StreamsConfig.DEFAULT_VALUE_SERDE_CLASS_CONFIG] = Serdes.String().javaClass
            return config
        }

    }

}
