package com.proffl.flink.app

import org.apache.flink.api.common.functions.FlatMapFunction
import org.apache.flink.api.common.functions.MapFunction
import org.apache.flink.api.java.ExecutionEnvironment
import org.apache.flink.api.java.tuple.Tuple2
import org.apache.flink.util.Collector
import scala.collection.SeqViewLike.FlatMapped

class WordCountApp : FlatMapFunction<String, Tuple2<String, Int>> {
    override fun flatMap(value: String, out: Collector<Tuple2<String, Int>>) {
        var words = value.split(" ")
        for (word in words) {
            out.collect(Tuple2<String, Int>(word, 1))
        }
    }

}
fun main() {
    var environment = ExecutionEnvironment.getExecutionEnvironment()
    var words = environment.readTextFile("/Users/proffl/TwilightStruggle/BigData/flink/src/main/resources/words.txt")

    var result = words.flatMap(WordCountApp()).groupBy(0).sum(1)
    result.print()

}