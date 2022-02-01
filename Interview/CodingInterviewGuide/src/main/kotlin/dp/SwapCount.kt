package dp


/**
 * given a number and an array of numbers, find method counts that sums of the given number by numbers.
 *
 * @level 2
 */
class SwapCount {
    companion object {
        fun swapCount(n: Int, arr: Array<Int>): Int {
            var tmp = Array(n + 1) { 0 }
            tmp[0] = 1
            for (k in arr) {
                for (i in k..n) {
                    tmp[i] += tmp[i - k]
                }
            }
            return tmp[n]
        }

    }
}

fun main() {
    var arr = arrayOf(2, 3, 5)
    for (i in 10..21) {
        println(SwapCount.swapCount(i, arr))
    }
}
