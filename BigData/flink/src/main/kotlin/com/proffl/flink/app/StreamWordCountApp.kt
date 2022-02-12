package com.proffl.flink.app

import org.apache.flink.api.java.functions.KeySelector
import org.apache.flink.api.java.tuple.Tuple2
import org.apache.flink.api.java.utils.ParameterTool
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import org.apache.flink.util.OutputTag

class StreamWordCountApp {
}

class WordCountKeySelector: KeySelector<Tuple2<String, Int>, String> {
    override fun getKey(value: Tuple2<String, Int>): String {
        return value.f0
    }
}

fun main(args: Array<String>) {
    var environment = StreamExecutionEnvironment.getExecutionEnvironment()
    environment.parallelism = 8
//    var words = environment.readTextFile("/Users/proffl/TwilightStruggle/BigData/flink/src/main/resources/words.txt")

    val params = ParameterTool.fromArgs(args)
    var host = params.get("host")
    var port = params.getInt("port")

    // open with nc -lk 7777
    var words = environment.socketTextStream(host, port) // 'default' slot group

    var result = words.flatMap(WordCountApp()).slotSharingGroup("green").keyBy(WordCountKeySelector()).sum(1).slotSharingGroup("red")

    val lateOutputTag = object : OutputTag<Tuple2<String, Int>>("late-data") {}
    words.flatMap(WordCountApp()).keyBy(WordCountKeySelector()).countWindow(2).sideOutputLateData(lateOutputTag)

    result.print()
    environment.execute()
}