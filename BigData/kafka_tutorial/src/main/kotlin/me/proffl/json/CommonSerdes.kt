package me.proffl.json

import org.apache.kafka.common.serialization.Deserializer
import org.apache.kafka.common.serialization.Serde
import org.apache.kafka.common.serialization.Serializer

class CommonSerdes<T>(var clz:Class<T>): Serde<T> {
    override fun serializer(): Serializer<T> {
        return CommonSerializer()
    }

    override fun deserializer(): Deserializer<T> {
        return CommonDeserializer(clz)
    }
}
