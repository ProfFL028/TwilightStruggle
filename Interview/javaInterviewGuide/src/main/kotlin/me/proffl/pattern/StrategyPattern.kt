package me.proffl.pattern


interface DiscountStrategy {
    fun discount(originalPay: Double): Double
}

class NoDiscountStrategy: DiscountStrategy {
    override fun discount(originalPay: Double): Double {
        return originalPay
    }
}

class Discount8Strategy: DiscountStrategy {
    override fun discount(originalPay: Double): Double {
        return originalPay * 0.8
    }
}

class Discount300minus100Strategy: DiscountStrategy {
    override fun discount(originalPay: Double): Double {
        val discount = originalPay / 300
        return originalPay - discount.toInt() * 100
    }
}

class DiscountContext(var strategy: DiscountStrategy) {
    fun getDiscount(originalPay: Double): Double {
        return strategy.discount(originalPay)
    }
}

fun main() {
    val discount8 = Discount8Strategy()
    val fullDiscount = NoDiscountStrategy()
    val discount300 = Discount300minus100Strategy()

    val context = DiscountContext(fullDiscount)
    println("full discount 1000 -> ${context.getDiscount(1000.0)}")
    context.strategy = discount8
    println("discount8 1000 -> ${context.getDiscount(1000.0)}")
    context.strategy = discount300
    println("discount300 1000 -> ${context.getDiscount(1000.0)}")
}