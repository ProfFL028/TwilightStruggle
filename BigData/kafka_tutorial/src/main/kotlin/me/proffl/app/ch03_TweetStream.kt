package me.proffl.app

import me.proffl.util.KafkaUtil
import org.apache.kafka.streams.KafkaStreams
import org.apache.kafka.streams.StreamsBuilder
import org.apache.kafka.streams.Topology
import org.apache.kafka.streams.kstream.Printed

fun main() {
    val topology = buildV1()

    val streams = KafkaStreams(topology, KafkaUtil.getDefaultConfig(id="dev"))

    Runtime.getRuntime().addShutdownHook(Thread(streams::close))
    println("Starting Twitter Streams")
    streams.start()
}

fun buildV1(): Topology {
    val builder = StreamsBuilder()
    val stream = builder.stream<Array<Byte>, Array<Byte>>("tweets")

    stream.print(Printed.toSysOut<Array<Byte>?, Array<Byte>?>().withLabel("tweets-stream"))
    return builder.build()
}
