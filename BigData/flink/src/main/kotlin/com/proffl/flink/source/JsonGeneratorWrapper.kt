package com.proffl.flink.source

import com.fasterxml.jackson.databind.ObjectMapper
import java.util.*

class JsonGeneratorWrapper<T>(
    var wrappedGenerator: BaseGenerator<T>
): BaseGenerator<String>() {
    init {
        this.maxRecordsPerSecond = wrappedGenerator.maxRecordsPerSecond
    }
    companion object {
        private val objectMapper = ObjectMapper()
    }

    override fun randomEvent(rnd: SplittableRandom, id: Long): String {
        var value = this.wrappedGenerator.randomEvent(rnd, id)
        return objectMapper.writeValueAsString(value)
    }
}


