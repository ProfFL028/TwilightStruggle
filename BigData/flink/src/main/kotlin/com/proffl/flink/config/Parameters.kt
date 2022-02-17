package com.proffl.flink.config

import org.apache.flink.api.java.utils.ParameterTool
import java.util.*


class Parameters(val tool: ParameterTool) {

    fun <T> getOrDefault(param: Param<T>): T {
        if (!tool.has(param.name)) {
            return param.defaultValue
        }

        var value: Any = when (param.type) {
            Integer::class.java -> tool.getInt(param.name)
            Long::class.java -> tool.getLong(param.name)
            Double::class.java -> tool.getDouble(param.name)
            Boolean::class.java -> tool.getBoolean(param.name)
            else -> tool.get(param.name)
        }
        return param.type.cast(value)
    }

    companion object {
        fun fromArgs(args: Array<String>): Parameters {
            var tool = ParameterTool.fromArgs(args)
            return Parameters(tool)
        }

        // Kafka:
        val KAFKA_HOST: Param<String> = Param.string("kafka-host", "localhost")
        val KAFKA_PORT: Param<Integer> = Param.integer("kafka-port", Integer(9092))

        val DATA_TOPIC: Param<String> = Param.string("data-topic", "livetransactions")
        val ALERTS_TOPIC: Param<String> = Param.string("alerts-topic", "alerts")
        val RULES_TOPIC: Param<String> = Param.string("rules-topic", "rules")
        val LATENCY_TOPIC: Param<String> = Param.string("latency-topic", "latency")
        val RULES_EXPORT_TOPIC: Param<String> = Param.string("current-rules-topic", "current-rules")

        val OFFSET: Param<String> = Param.string("offset", "latest")

        // GCP PubSub:
        val GCP_PROJECT_NAME: Param<String> = Param.string("gcp-project", "da-fe-212612")
        val GCP_PUBSUB_RULES_SUBSCRIPTION: Param<String> = Param.string("pubsub-rules", "rules-demo")
        val GCP_PUBSUB_ALERTS_SUBSCRIPTION: Param<String> = Param.string("pubsub-alerts", "alerts-demo")
        val GCP_PUBSUB_LATENCY_SUBSCRIPTION: Param<String> = Param.string("pubsub-latency", "latency-demo")
        val GCP_PUBSUB_RULES_EXPORT_SUBSCRIPTION: Param<String> =
            Param.string("pubsub-rules-export", "current-rules-demo")

        // Socket
        val SOCKET_PORT: Param<Integer> = Param.integer("pubsub-rules-export", Integer(9999))

        // General:
        //    source/sink types: kafka / pubsub / socket
        val RULES_SOURCE: Param<String> = Param.string("rules-source", "SOCKET")
        val TRANSACTIONS_SOURCE: Param<String> = Param.string("data-source", "GENERATOR")
        val ALERTS_SINK: Param<String> = Param.string("alerts-sink", "STDOUT")
        val LATENCY_SINK: Param<String> = Param.string("latency-sink", "STDOUT")
        val RULES_EXPORT_SINK: Param<String> = Param.string("rules-export-sink", "STDOUT")

        val RECORDS_PER_SECOND: Param<Integer> = Param.integer("records-per-second", Integer(2))

        val LOCAL_MODE_DISABLE_WEB_UI = "-1"

        val LOCAL_EXECUTION: Param<String> = Param.string("local", LOCAL_MODE_DISABLE_WEB_UI)

        val SOURCE_PARALLELISM: Param<Integer> = Param.integer("source-parallelism", Integer(2))
        val SINK_PARALLELISM: Param<Integer> = Param.integer("sink-parallelism", Integer(1))
        val CHECKPOINT_INTERVAL: Param<Integer> = Param.integer("checkpoint-interval", Integer(600000))
        val MIN_PAUSE_BETWEEN_CHECKPOINTS: Param<Integer> = Param.integer("min-pause-btwn-checkpoints", Integer(600000))
        val OUT_OF_ORDERNESS: Param<Integer> = Param.integer("out-of-orderdness", Integer(500))

        //  List<Param> list = Arrays.asList(new String[]{"foo", "bar"});

        //  List<Param> list = Arrays.asList(new String[]{"foo", "bar"});
        val STRING_PARAMS: List<Param<String>> = Arrays.asList<Param<String>>(
            LOCAL_EXECUTION,
            KAFKA_HOST,
            DATA_TOPIC,
            ALERTS_TOPIC,
            RULES_TOPIC,
            LATENCY_TOPIC,
            RULES_EXPORT_TOPIC,
            OFFSET,
            GCP_PROJECT_NAME,
            GCP_PUBSUB_RULES_SUBSCRIPTION,
            GCP_PUBSUB_ALERTS_SUBSCRIPTION,
            GCP_PUBSUB_LATENCY_SUBSCRIPTION,
            GCP_PUBSUB_RULES_EXPORT_SUBSCRIPTION,
            RULES_SOURCE,
            TRANSACTIONS_SOURCE,
            ALERTS_SINK,
            LATENCY_SINK,
            RULES_EXPORT_SINK
        )

        val INT_PARAMS: List<Param<Integer>> = Arrays.asList<Param<Integer>>(
            KAFKA_PORT,
            SOCKET_PORT,
            RECORDS_PER_SECOND,
            SOURCE_PARALLELISM,
            SINK_PARALLELISM,
            CHECKPOINT_INTERVAL,
            MIN_PAUSE_BETWEEN_CHECKPOINTS,
            OUT_OF_ORDERNESS
        )

        val BOOL_PARAMS: List<Param<Boolean>> = Collections.emptyList()
    }

}