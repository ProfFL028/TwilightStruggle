package me.proffl.json

import com.google.gson.Gson
import org.apache.kafka.common.serialization.Deserializer
import java.nio.charset.StandardCharsets

class CommonDeserializer<T>(var clz: Class<T>): Deserializer<T> {
    private val gson = Gson()

    override fun deserialize(topic: String, data: ByteArray?): T? {
        if (data == null)
            return null
        return gson.fromJson(String(data, StandardCharsets.UTF_8), clz)
    }
}
