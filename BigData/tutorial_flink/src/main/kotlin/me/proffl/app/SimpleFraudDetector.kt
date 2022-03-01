package me.proffl.app

import me.proffl.SimpleFraudDetector
import me.proffl.entity.Transaction
import me.proffl.entity.TransactionKeySelector
import me.proffl.sink.AlertLogSink
import me.proffl.source.TransactionSource
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment

fun main() {
    val env = StreamExecutionEnvironment.getExecutionEnvironment()

    val transactionStream = env.addSource(TransactionSource()).name("transaction")
    val alertStream = transactionStream.keyBy(TransactionKeySelector())
        .process(SimpleFraudDetector()).name("fraudDetector")

    alertStream.addSink(AlertLogSink()).name("send-alerts-log")

    env.execute()
}