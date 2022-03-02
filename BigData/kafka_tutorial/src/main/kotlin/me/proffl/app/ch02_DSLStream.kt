package me.proffl.app

import me.proffl.util.KafkaUtil
import org.apache.kafka.streams.KafkaStreams
import org.apache.kafka.streams.StreamsBuilder

/**
 * 1. docker-compose up
 * 2. docker-compose exec kafka bash
 * 3. kafka-console-producer --bootstrap-server localhost:9092 --topic users
 */

fun main() {
    val builder = StreamsBuilder()
    val stream = builder.stream<Void, String>("users")

    stream.foreach { _, value ->
        println("(DSL) Hello, $value")
    }

    val streams = KafkaStreams(builder.build(), KafkaUtil.getDefaultConfig())
    streams.start()

    Runtime.getRuntime().addShutdownHook(Thread(streams::close))
}
