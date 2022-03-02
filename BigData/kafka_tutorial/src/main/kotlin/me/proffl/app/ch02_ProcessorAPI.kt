package me.proffl.app

import me.proffl.processor.SayHelloProcessor
import me.proffl.util.KafkaUtil
import org.apache.kafka.streams.KafkaStreams
import org.apache.kafka.streams.Topology
import org.apache.kafka.streams.processor.api.ProcessorSupplier


fun main() {
    val topology = Topology()
    topology.addSource("UserSource", "users")
    topology.addProcessor("SayHello", ProcessorSupplier { SayHelloProcessor() }, "UserSource")

    val streams = KafkaStreams(topology, KafkaUtil.getDefaultConfig())
    streams.start()
    Runtime.getRuntime().addShutdownHook(Thread(streams::close))
}
