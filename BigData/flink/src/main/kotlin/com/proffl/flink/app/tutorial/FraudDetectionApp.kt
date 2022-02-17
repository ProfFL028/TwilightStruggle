package com.proffl.flink.app.tutorial

import com.proffl.flink.config.Config
import com.proffl.flink.config.Parameters
import com.proffl.flink.config.Parameters.Companion.CHECKPOINT_INTERVAL
import com.proffl.flink.config.Parameters.Companion.MIN_PAUSE_BETWEEN_CHECKPOINTS
import com.proffl.flink.config.Parameters.Companion.RECORDS_PER_SECOND
import com.proffl.flink.source.JsonGeneratorWrapper
import com.proffl.flink.source.TransactionGenerator
import com.proffl.flink.source.TransactionSource
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment

fun main(args: Array<String>) {
    var parameters = Parameters.fromArgs(args)
    var config = Config.fromParameters(parameters)


    var env = StreamExecutionEnvironment.getExecutionEnvironment()

    env.checkpointConfig.checkpointInterval = config.get(CHECKPOINT_INTERVAL).toLong()
    env.checkpointConfig.minPauseBetweenCheckpoints = config.get(MIN_PAUSE_BETWEEN_CHECKPOINTS).toLong()

    var transactions = env.addSource(TransactionSource.createTransactionSource(config)).name("transaction")
    transactions.print()
    env.execute()
}
