package me.proffl.app

import com.mitchseymour.kafka.serialization.avro.AvroSerdes
import me.proffl.entity.DummyTranslate
import me.proffl.entity.Tweet
import me.proffl.json.CommonSerdes
import me.proffl.util.KafkaUtil
import org.apache.kafka.common.serialization.Serdes
import org.apache.kafka.streams.KafkaStreams
import org.apache.kafka.streams.KeyValue
import org.apache.kafka.streams.StreamsBuilder
import org.apache.kafka.streams.Topology
import org.apache.kafka.streams.kstream.Consumed
import org.apache.kafka.streams.kstream.Printed
import org.apache.kafka.streams.kstream.Produced
import java.nio.charset.StandardCharsets

fun main() {
    val topology = buildV2()

    val streams = KafkaStreams(topology, KafkaUtil.getDefaultConfig(id = "dev"))

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

    val filtered = stream.filterNot { _, tweet -> tweet != null && !tweet.retweet }
    val englishTweet = { _: ByteArray?, tweet: Tweet? -> tweet != null && tweet.lang == "en" }
    val nonEnglishTweet = { _: ByteArray?, tweet: Tweet? -> tweet != null && tweet.lang != "en" }

    val branches = filtered.branch(englishTweet, nonEnglishTweet)
    val englishBranch = branches[0]
    val nonEnglishBranch = branches[1]

    englishBranch.print(Printed.toSysOut<ByteArray?, Tweet?>().withLabel("english tweet"))
    nonEnglishBranch.print(Printed.toSysOut<ByteArray?, Tweet?>().withLabel("nonEnglish tweet"))

    val translatedStream = nonEnglishBranch.map { _, tweet ->
        val newKey = tweet.id.toString().toByteArray(StandardCharsets.UTF_8)
        val translatedTweet = DummyTranslate().translate(tweet)
        KeyValue.pair(newKey, translatedTweet)
    }
    // nonEnglishBranch.mapValues { tweet -> DummyTranslate().translate(tweet) } // simplify if we don't need to modify the key

    englishBranch.merge(translatedStream)

    // to avro
    // sink processor
    englishBranch.to("crypto-sentiment")
    return builder.build()
}

