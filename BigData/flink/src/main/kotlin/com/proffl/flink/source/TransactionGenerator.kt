package com.proffl.flink.source

import com.proffl.flink.model.Transaction
import java.util.*
import java.util.concurrent.ThreadLocalRandom
import kotlin.math.floor

class TransactionGenerator(maxRecordsPerSecond: Int=-1) : BaseGenerator<Transaction>(maxRecordsPerSecond) {
    override fun randomEvent(rnd: SplittableRandom, id: Long): Transaction {
        var transaction = Transaction()
        transaction.transactionId = rnd.nextLong(Long.MAX_VALUE)
        transaction.payeeId = rnd.nextLong(MAX_PAYEE_ID)
        transaction.beneficiaryId = rnd.nextLong(MAX_BENEFICIARY_ID)
        var paymentAmountDouble = ThreadLocalRandom.current().nextDouble(MIN_PAYMENT_AMOUNT, MAX_PAYMENT_AMOUNT)
        transaction.paymentAmount = (floor(paymentAmountDouble * 100) / 100).toBigDecimal()
        transaction.paymentType = paymentType(transaction.transactionId)
        transaction.eventTime = System.currentTimeMillis()
        transaction.ingestionTimestamp = System.currentTimeMillis()
        return transaction
    }

    private fun paymentType(id: Long): Transaction.PaymentType {
        return if (Math.floorMod(id.toInt(), 2) == 0) Transaction.PaymentType.CRD else Transaction.PaymentType.CSH
    }

    companion object {
        private const val MAX_PAYEE_ID = 100000L
        private const val MAX_BENEFICIARY_ID = 100000L

        private const val MAX_PAYMENT_AMOUNT: Double = 5.0
        private const val MIN_PAYMENT_AMOUNT: Double = 20.0

    }
}