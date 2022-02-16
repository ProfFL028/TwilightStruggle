package com.proffl.flink.schema

import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule
import com.proffl.flink.model.InputMessage
import org.apache.flink.api.common.serialization.DeserializationSchema
import org.apache.flink.api.common.typeinfo.TypeInformation
import java.time.LocalDateTime

class InputMessageDeserializationSchema : DeserializationSchema<InputMessage> {
    companion object {
        var objMapper: ObjectMapper = ObjectMapper().registerModule(JavaTimeModule())

    }

    override fun deserialize(message: ByteArray?): InputMessage {
        try {
            return objMapper.readValue(message, InputMessage::class.java)
        } catch(e:Exception) {
            return InputMessage("system", "output", LocalDateTime.now(), "Parse Error!!")
        }
    }

    override fun isEndOfStream(nextElement: InputMessage?): Boolean {
        return false
    }

    override fun getProducedType(): TypeInformation<InputMessage> {
        return TypeInformation.of(InputMessage::class.java)
    }
}
