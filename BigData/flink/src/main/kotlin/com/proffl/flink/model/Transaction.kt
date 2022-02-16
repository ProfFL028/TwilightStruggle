package com.proffl.flink.model

import com.proffl.flink.source.TransactionSource
import com.sun.javaws.exceptions.InvalidArgumentException
import java.math.BigDecimal
import java.time.ZoneOffset
import java.time.ZonedDateTime
import java.time.format.DateTimeFormatter
import java.util.*

data class Transaction(
    var transactionId: Long = 0,
    var eventTime: Long = 0,
    var payeeId: Long = 0,
    var beneficiaryId: Long = 0,
    var paymentType: PaymentType = PaymentType.CSH,
    var paymentAmount: BigDecimal = BigDecimal(0),
    var ingestionTimestamp: Long = 0
): TimestampAssignable<Long> {
    override fun assignIngestionTimestamp(timestamp: Long) {
        this.ingestionTimestamp = timestamp
    }

    companion object {
        val timeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss").withLocale(Locale.CHINA).withZone(ZoneOffset.UTC)

        fun fromString(line: String): Transaction {
            var tokens = line.split(",")
            var numTokens = 7
            if (tokens.size != numTokens) {
                throw RuntimeException("Invalid transaction input: $line")
            }
            var transaction = Transaction()

            try {
                var iter = tokens.iterator()
                transaction.transactionId = iter.next().toLong()
                transaction.eventTime = ZonedDateTime.parse(iter.next(), timeFormatter).toInstant().toEpochMilli()
                transaction.payeeId = iter.next().toLong()
                transaction.beneficiaryId = iter.next().toLong()
                transaction.paymentType = PaymentType.valueOf(iter.next())
                transaction.paymentAmount = BigDecimal(iter.next())
                transaction.ingestionTimestamp = iter.next().toLong()
            } catch (e: NumberFormatException) {
                throw RuntimeException("Invalid transaction input: $line")
            }
            return transaction
        }
    }

    enum class PaymentType(var representation: String) {
        CSH("CSH"),
        CRD("CRD"),
    }
}