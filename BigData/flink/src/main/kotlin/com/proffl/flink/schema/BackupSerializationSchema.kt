package com.proffl.flink.schema

import com.fasterxml.jackson.core.JsonProcessingException
import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule
import com.proffl.flink.model.Backup
import org.apache.flink.api.common.serialization.SerializationSchema


class BackupSerializationSchema : SerializationSchema<Backup> {
    companion object {
        var objectMapper: ObjectMapper = ObjectMapper().registerModule(JavaTimeModule())
    }

    override fun serialize(backupMessage: Backup?): ByteArray? {
        try {
            val json: String = objectMapper.writeValueAsString(backupMessage)
            return json.toByteArray()
        } catch (e: JsonProcessingException) {
        }
        return ByteArray(0)
    }
}
