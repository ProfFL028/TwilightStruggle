package me.proffl.json

import com.google.gson.Gson
import org.apache.kafka.common.serialization.Deserializer
import org.slf4j.Logger
import org.slf4j.LoggerFactory
import java.nio.charset.StandardCharsets

class CommonDeserializer<T>(var clz: Class<T>) : Deserializer<T> {
    private val gson = Gson()

    companion object {
        val logger: Logger = LoggerFactory.getLogger(CommonDeserializer::class.java)
    }

    override fun deserialize(topic: String, data: ByteArray?): T? {
        if (data == null)
            return null
        return try {
            gson.fromJson(String(data, StandardCharsets.UTF_8), clz)
        } catch (e: Exception) {
            logger.error(e.message)
            return null
        }
    }
}
