package me.proffl.entity

import me.proffl.source.TransactionSource
import org.apache.flink.api.java.functions.KeySelector

data class Transaction(
    var accountId: Long = 0L,
    var timestamp: Long = 0L,
    var amount: Double = 0.0
): java.io.Serializable  {
    companion object {
        const val serialVersionUID = 1L
    }
    override fun toString(): String {
        return "accountId: $accountId, timestamp: $timestamp, amount: $amount"
    }
}

class TransactionKeySelector: KeySelector<Transaction, Long> {
    override fun getKey(value: Transaction): Long {
        return value.accountId
    }

}

