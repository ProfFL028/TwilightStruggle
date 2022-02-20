package com.proffl.flink.app.tutorial

import com.fasterxml.jackson.databind.ObjectMapper
import com.proffl.flink.config.Config
import com.proffl.flink.config.Parameters
import com.proffl.flink.config.Parameters.Companion.CHECKPOINT_INTERVAL
import com.proffl.flink.config.Parameters.Companion.MIN_PAUSE_BETWEEN_CHECKPOINTS
import com.proffl.flink.config.Parameters.Companion.OUT_OF_ORDERNESS
import com.proffl.flink.config.Parameters.Companion.RECORDS_PER_SECOND
import com.proffl.flink.model.Keyed
import com.proffl.flink.model.KeyedKeySelector
import com.proffl.flink.model.Rule
import com.proffl.flink.model.Rule.Companion.ruleDescriptor
import com.proffl.flink.model.Transaction
import com.proffl.flink.operator.DynamicAlertFunction
import com.proffl.flink.operator.DynamicKeyFunction
import com.proffl.flink.source.*
import com.proffl.flink.source.RulesStaticJsonGenerator.Companion.RULES
import com.proffl.flink.times.SimpleBoundedOutOfOrdernessTimestampExtractor
import org.apache.flink.api.common.eventtime.*
import org.apache.flink.api.common.typeinfo.TypeHint
import org.apache.flink.api.common.typeinfo.TypeInformation
import org.apache.flink.streaming.api.datastream.BroadcastStream
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import java.lang.reflect.ParameterizedType
import java.lang.reflect.Type
import java.time.Duration
import javax.print.attribute.IntegerSyntax

fun main(args: Array<String>) {
    var parameters = Parameters.fromArgs(args)
    var config = Config.fromParameters(parameters)

    var env = StreamExecutionEnvironment.getExecutionEnvironment()

    env.checkpointConfig.checkpointInterval = config.get(CHECKPOINT_INTERVAL).toLong()
    env.checkpointConfig.minPauseBetweenCheckpoints = config.get(MIN_PAUSE_BETWEEN_CHECKPOINTS).toLong()

    var ruleStringStream = env.addSource(RuleSource.createRolesSource(config)).setParallelism(1)
    var ruleStream = RuleSource.stringSourceToRules(ruleStringStream)
    val rulesStream =  ruleStream.broadcast(ruleDescriptor)

    var transactionsStringStream = env.addSource(TransactionSource.createTransactionSource(config)).name("transaction source")
    var transactionStream = TransactionSource.stringsToTransaction(transactionsStringStream)
        .assignTimestampsAndWatermarks(WatermarkStrategy.forBoundedOutOfOrderness<Transaction>(
            Duration.ofMillis(config.get(OUT_OF_ORDERNESS).toLong()))
            .withTimestampAssigner { event, _ -> event.eventTime })

    val alertStream = transactionStream.connect(rulesStream).process(DynamicKeyFunction()).uid("DynamicKeyFunction")
        .name("Dynamic Partitioning Function")
        .returns(TypeInformation.of(
            KeyedTypeHint()
        ))
        .keyBy(KeyedKeySelector())
        // .keyBy {event -> event.key} // currently not supported by kotlin
        .connect(rulesStream).process(DynamicAlertFunction())
        .uid("DynamicAlertFunction")
        .name("Dynamic Rule Evaluation Function");

    alertStream.print()
    env.execute()
}

class KeyedTypeHint: TypeHint<Keyed<Transaction, String, Integer>>() {}

fun getType(raw: Class<*>, vararg args: Type) = object : ParameterizedType {
    override fun getRawType(): Type = raw
    override fun getActualTypeArguments(): Array<out Type> = args
    override fun getOwnerType(): Type? = null
}

