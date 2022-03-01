package me.proffl

import me.proffl.entity.Alert
import me.proffl.entity.Transaction
import org.apache.flink.streaming.api.functions.KeyedProcessFunction
import org.apache.flink.util.Collector

class SimpleFraudDetector: KeyedProcessFunction<Long, Transaction, Alert>() {
    override fun processElement(value: Transaction, ctx: Context, out: Collector<Alert>) {
        out.collect(Alert(value.accountId))
    }
}