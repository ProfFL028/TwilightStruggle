package dp

import java.lang.Math.max
import java.lang.Math.pow


/**
 * Given some goods and its corresponding weight and calories. Find the max calories it can get with a corresponding max calories.
 * (can't fraction)
 */
data class Food(var name: String = "", var weight: Int = 0, var calories: Int = 0)

class MaxBag {
    companion object {
        fun find(foods: Array<Food>, maxWeight: Int): Int {

            return findDP(foods, maxWeight)
        }

        fun findDP(foods: Array<Food>, maxWeight: Int): Int {

            var dp = Array(maxWeight + 1) { Array(foods.size + 1) { 0 } }

            for (i in 1..maxWeight) {
                var curMax = 0
                for (j in foods.indices) {
                    var exWeight = i - foods[j].weight
                    if (exWeight >= 0 && dp[exWeight][j] == 0) {
                        if (curMax < (dp[exWeight][j] + foods[j].calories)) {
                            curMax = dp[exWeight][foods.size] + foods[j].calories

                            for (k in foods.indices) {
                                dp[i][k] = dp[exWeight][k]
                            }
                            dp[i][j] = 1

                        }
                    }
                }
                dp[i][foods.size] = curMax
                if (curMax < dp[i-1][foods.size]) {
                    for (k in 0..foods.size) {
                        dp[i][k] = dp[i-1][k]
                    }
                }

            }
            return dp[maxWeight][foods.size]
        }

        fun findBruteForce(foods: Array<Food>, maxWeight: Int): Int {
            var epoch = pow2(foods.size)
            var maxCalc = 0
            for (i in 0 until epoch.toInt()) {
                var j = i
                var totalWeight = 0
                var totalCalories = 0
                for (k in foods.indices) {
                    if (j % 2 == 0) {
                        totalWeight += foods[k].weight
                        totalCalories += foods[k].calories
                    }
                    j /= 2
                }
                if (totalWeight <= maxWeight) {
                    maxCalc = maxCalc.coerceAtLeast(totalCalories)
                }

            }
            return maxCalc
        }

        private fun pow2(k: Int): Double {
            var result = 1.0
            var pre = 2.0
            var p = k
            while (p > 0) {
                if (p % 2 == 1) {
                    result *= pre
                }
                pre *= pre
                p /= 2
            }
            return result
        }
    }
}

fun main() {
    var food1 = Food("potatoes", 800, 1501600)
    var food2 = Food("Wheat flour", 400, 1444000)
    var food3 = Food("Rice", 300, 1122000)
    var food4 = Food("Beans", 300, 690000)
    var food5 = Food("Tomatoes", 300, 237000)
    var food6 = Food("Strawberry jain", 50, 130000)
    var food7 = Food("peanut butter", 20, 117800)

    var foods = arrayOf(food1, food2, food3, food4, food5, food6, food7)

    println(MaxBag.find(foods, 1000))

}
