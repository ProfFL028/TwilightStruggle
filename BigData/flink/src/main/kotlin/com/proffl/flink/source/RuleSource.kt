package com.proffl.flink.source

import com.proffl.flink.config.Config
import com.proffl.flink.config.KafkaUtils
import com.proffl.flink.config.Parameters
import com.proffl.flink.config.Parameters.Companion.RULES_SOURCE
import com.proffl.flink.config.Parameters.Companion.SOCKET_PORT
import com.proffl.flink.model.Rule
import com.proffl.flink.stream.JsonDeserialize
import org.apache.flink.api.common.eventtime.WatermarkStrategy
import org.apache.flink.api.common.serialization.SimpleStringSchema
import org.apache.flink.streaming.api.datastream.DataStream
import org.apache.flink.streaming.api.functions.source.SocketTextStreamFunction
import org.apache.flink.streaming.api.functions.source.SourceFunction
import org.apache.flink.streaming.connectors.kafka.FlinkKafkaConsumer
import java.time.Duration
import java.util.*


class RuleSource {
    companion object {
        fun createRolesSource(config: Config): SourceFunction<String> {
            var sourceType = config.get(RULES_SOURCE)
            var ruleSourceType = Type.valueOf(sourceType)

            when (ruleSourceType) {
                Type.KAFKA -> {
                    val properties = KafkaUtils.initConsumerProperties(config)
                    val transactionTopic = config.get(Parameters.RULES_TOPIC)
                    val kafkaConsumer = FlinkKafkaConsumer(transactionTopic, SimpleStringSchema(), properties)
                    //                    KafkaSource.builder<Transaction>()
                    //                    .setTopics(transactionTopic)
                    //                    .setStartingOffsets(OffsetsInitializer.latest())
                    //                    .setProperties(properties)
                    //                    .build()
                    kafkaConsumer.setStartFromLatest()
                    return kafkaConsumer
                }
                Type.SOCKET -> {
                    return SocketTextStreamFunction("localhost", config.get(SOCKET_PORT).toInt(), "\n", -1L)
                }
                Type.STATIC -> {
                    return RulesStaticJsonGenerator()
                }
                else -> {
                    throw RuntimeException("Invalid rule type: $ruleSourceType")
                }
            }
        }

        fun stringSourceToRules(ruleString: DataStream<String>): DataStream<Rule> {
            return ruleString.flatMap(JsonDeserialize(Rule::class.java))
                .returns(Rule::class.java)
                .assignTimestampsAndWatermarks(
                    WatermarkStrategy.forBoundedOutOfOrderness(
                        Duration.ofMillis(Long.MAX_VALUE)
                    )
                )
        }

    }

    enum class Type(val roleType: String) {
        KAFKA("Rules Source (Kafka)"),
        PUBSUB("Rules Source (Pub/Sub)"),
        SOCKET("Rules Source (Socket)"),
        STATIC("Rules Source (Static Ruleset)");
    }
}

class RulesStaticJsonGenerator : BaseGenerator<String>(1) {
    override fun randomEvent(rnd: SplittableRandom, id: Long): String {
        return if (id >= 0 && id < RULES.size) {
            RULES[id.toInt()]
        } else {
            return RULES[0]
        }
    }

    companion object {
        val RULES = arrayOf(
            "{\"ruleId\":\"1\","
                    + "\"aggregateFieldName\":\"paymentAmount\","
                    + "\"aggregatorFunctionType\":\"SUM\","
                    + "\"groupingKeyNames\":[\"payeeId\", \"beneficiaryId\"],"
                    + "\"limit\":\"20000000\","
                    + "\"limitOperatorType\":\"GREATER\","
                    + "\"ruleState\":\"ACTIVE\","
                    + "\"windowMinutes\":\"43200\"}",
            ("{\"ruleId\":\"2\","
                    + "\"aggregateFieldName\":\"COUNT_FLINK\","
                    + "\"aggregatorFunctionType\":\"SUM\","
                    + "\"groupingKeyNames\":[\"paymentType\"],"
                    + "\"limit\":\"300\","
                    + "\"limitOperatorType\":\"LESS\","
                    + "\"ruleState\":\"PAUSE\","
                    + "\"windowMinutes\":\"1440\"}"),
            ("{\"ruleId\":\"3\","
                    + "\"aggregateFieldName\":\"paymentAmount\","
                    + "\"aggregatorFunctionType\":\"SUM\","
                    + "\"groupingKeyNames\":[\"beneficiaryId\"],"
                    + "\"limit\":\"10000000\","
                    + "\"limitOperatorType\":\"GREATER_EQUAL\","
                    + "\"ruleState\":\"ACTIVE\","
                    + "\"windowMinutes\":\"1440\"}"),
            ("{\"ruleId\":\"4\","
                    + "\"aggregateFieldName\":\"COUNT_WITH_RESET_FLINK\","
                    + "\"aggregatorFunctionType\":\"SUM\","
                    + "\"groupingKeyNames\":[\"paymentType\"],"
                    + "\"limit\":\"100\","
                    + "\"limitOperatorType\":\"GREATER_EQUAL\","
                    + "\"ruleState\":\"ACTIVE\","
                    + "\"windowMinutes\":\"1440\"}")
        )
    }
}