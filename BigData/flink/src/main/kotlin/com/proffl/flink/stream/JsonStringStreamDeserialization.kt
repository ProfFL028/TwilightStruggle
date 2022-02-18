package com.proffl.flink.stream

import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.databind.json.JsonMapper
import org.apache.flink.api.common.functions.RichFlatMapFunction
import org.apache.flink.configuration.Configuration
import org.apache.flink.streaming.api.datastream.DataStream
import org.apache.flink.util.Collector

class JsonStringStreamDeserialization {
    companion object {
        fun <T> deserialization(jsonStringStream: DataStream<String>, clz: Class<T>):DataStream<T> {
            return jsonStringStream.flatMap(JsonDeserialize(clz))
        }
     }
}

class JsonDeserialize<T> (
    private var targetClz: Class<T>
): RichFlatMapFunction<String, T>() {
    private lateinit var parser: ObjectMapper

    override fun open(parameters: Configuration?) {
        super.open(parameters)
        parser = ObjectMapper()
    }

    override fun flatMap(value: String, out: Collector<T>) {
        out.collect(parser.readValue(value, targetClz))
    }

}