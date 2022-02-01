package dp

import java.lang.Integer.min

/**
 * MinSwapCount, given a number and an array of numbers. find the min count to combine the given number using given numbers.
 *
 * @level 2
 */
class MinSwapCount {
    companion object {
        fun minSwapCount(n: Int, arr: Array<Int>): Int {
            var tmp = Array(n + 1) { Int.MAX_VALUE }
            tmp[0] = 0
            for (i in 1..n) {
                var min = Int.MAX_VALUE
                for (k in arr) {
                    if (i >= k) {
                        min = min(min, tmp[i - k])
                    }
                }
                if (min != Int.MAX_VALUE) {
                    tmp[i] = min + 1
                }
            }

            return tmp[n]
        }
    }

}

fun main() {
    var arr = arrayOf(2,3,5)
    println(MinSwapCount.minSwapCount(21, arr))
}
