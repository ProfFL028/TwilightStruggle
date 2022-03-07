package me.proffl.app

import me.proffl.entity.Tweet
import me.proffl.json.CommonSerdes
import me.proffl.util.KafkaUtil
import org.apache.kafka.common.serialization.Serdes
import org.apache.kafka.streams.KafkaStreams
import org.apache.kafka.streams.StreamsBuilder
import org.apache.kafka.streams.Topology
import org.apache.kafka.streams.kstream.Consumed
import org.apache.kafka.streams.kstream.Printed

fun main() {
    val topology = buildV2()

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

fun buildV2(): Topology {
    val builder = StreamsBuilder()
    val stream = builder.stream("tweets", Consumed.with(Serdes.ByteArray(), CommonSerdes(Tweet::class.java)))
    stream.print(Printed.toSysOut<ByteArray, Tweet>().withLabel("tweets-stream"))

    return builder.build()
}

