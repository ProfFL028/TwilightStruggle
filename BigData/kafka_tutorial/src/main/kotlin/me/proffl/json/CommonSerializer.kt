package me.proffl.json

import com.google.gson.Gson
import org.apache.kafka.common.serialization.Serializer
import java.nio.charset.StandardCharsets

class CommonSerializer<T>: Serializer<T> {
    private val gson = Gson()

    override fun serialize(topic: String, data: T): ByteArray {
        return gson.toJson(data).toByteArray(StandardCharsets.UTF_8)
    }

}
