package com.proffl.flink.source

import com.proffl.flink.config.Config
import com.proffl.flink.config.KafkaUtils
import com.proffl.flink.config.Parameters.Companion.DATA_TOPIC
import com.proffl.flink.config.Parameters.Companion.RECORDS_PER_SECOND
import com.proffl.flink.config.Parameters.Companion.TRANSACTIONS_SOURCE
import com.proffl.flink.model.Transaction
import com.proffl.flink.times.TimeStamper
import com.proffl.flink.stream.JsonDeserialize
import org.apache.flink.api.common.serialization.SimpleStringSchema
import org.apache.flink.streaming.api.datastream.DataStream
import org.apache.flink.streaming.api.functions.source.SourceFunction
import org.apache.flink.streaming.connectors.kafka.FlinkKafkaConsumer

class TransactionSource {
    companion object {
        fun createTransactionSource(config: Config): SourceFunction<String>? {
            val sourceType = config.get(TRANSACTIONS_SOURCE)
            val transactionSourceType = Type.valueOf(sourceType.uppercase())

             if (transactionSourceType == Type.KAFKA) {
                val properties = KafkaUtils.initConsumerProperties(config)
                val transactionTopic = config.get(DATA_TOPIC)
                val kafkaConsumer =  FlinkKafkaConsumer(transactionTopic, SimpleStringSchema(), properties)
        //                    KafkaSource.builder<Transaction>()
        //                    .setTopics(transactionTopic)
        //                    .setStartingOffsets(OffsetsInitializer.latest())
        //                    .setProperties(properties)
        //                    .build()
                kafkaConsumer.setStartFromLatest()
                return kafkaConsumer
            } else {
                val transactionPerSecond = config.get(RECORDS_PER_SECOND).toInt()
                return JsonGeneratorWrapper(TransactionGenerator(transactionPerSecond))
            }
        }

        fun stringsToTransaction(transactionsStringStream: DataStream<String>): DataStream<Transaction> {
            return transactionsStringStream.flatMap(JsonDeserialize(Transaction::class.java))
                .returns(Transaction::class.java)
                .returns(Transaction::class.java)
                .name("Transaction Object")
        }
    }

    enum class Type(val typeName: String) {
        GENERATOR("Transactions Source (generated locally)"),
        KAFKA("Transactions Source(Kafka)")
    }
}