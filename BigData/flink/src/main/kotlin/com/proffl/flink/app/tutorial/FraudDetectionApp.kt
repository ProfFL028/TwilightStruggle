package com.proffl.flink.app.tutorial

import com.fasterxml.jackson.databind.ObjectMapper
import com.proffl.flink.config.Config
import com.proffl.flink.config.Parameters
import com.proffl.flink.config.Parameters.Companion.CHECKPOINT_INTERVAL
import com.proffl.flink.config.Parameters.Companion.MIN_PAUSE_BETWEEN_CHECKPOINTS
import com.proffl.flink.config.Parameters.Companion.OUT_OF_ORDERNESS
import com.proffl.flink.config.Parameters.Companion.RECORDS_PER_SECOND
import com.proffl.flink.model.Rule
import com.proffl.flink.model.Transaction
import com.proffl.flink.source.*
import com.proffl.flink.source.RulesStaticJsonGenerator.Companion.RULES
import com.proffl.flink.times.SimpleBoundedOutOfOrdernessTimestampExtractor
import org.apache.flink.api.common.eventtime.*
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import java.time.Duration

fun main(args: Array<String>) {
    var parameters = Parameters.fromArgs(args)
    var config = Config.fromParameters(parameters)

    var env = StreamExecutionEnvironment.getExecutionEnvironment()

    env.checkpointConfig.checkpointInterval = config.get(CHECKPOINT_INTERVAL).toLong()
    env.checkpointConfig.minPauseBetweenCheckpoints = config.get(MIN_PAUSE_BETWEEN_CHECKPOINTS).toLong()

    var ruleStringStream = env.addSource(RuleSource.createRolesSource(config)).setParallelism(1)
    var ruleStream = RuleSource.stringSourceToRules(ruleStringStream)

    var transactionsStringStream = env.addSource(TransactionSource.createTransactionSource(config)).name("transaction source")
    var transactionStream = TransactionSource.stringsToTransaction(transactionsStringStream)
        .assignTimestampsAndWatermarks(WatermarkStrategy.forBoundedOutOfOrderness<Transaction>(
            Duration.ofMillis(config.get(OUT_OF_ORDERNESS).toLong()))
            .withTimestampAssigner { event, _ -> event.eventTime })

    ruleStream.print()
    env.execute()
}
