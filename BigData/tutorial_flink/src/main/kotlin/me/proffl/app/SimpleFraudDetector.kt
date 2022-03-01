package me.proffl.app

import me.proffl.job.SimpleFraudDetector
import me.proffl.entity.TransactionKeySelector
import me.proffl.job.ValueStatedFraudDetector
import me.proffl.sink.AlertLogSink
import me.proffl.source.TransactionSource
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment

fun main() {
    val env = StreamExecutionEnvironment.getExecutionEnvironment()

    val transactionStream = env.addSource(TransactionSource()).name("transaction")
    val alertStream = transactionStream.keyBy(TransactionKeySelector())
        .process(ValueStatedFraudDetector()).name("fraudDetector")

    alertStream.addSink(AlertLogSink()).name("send-alerts-log")

    env.execute()
}