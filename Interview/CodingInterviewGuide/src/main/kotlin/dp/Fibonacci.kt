package dp

/**
 * @content Calculate the Nth element in Fibonacci.
 * @requires O(log(n)) time speed.
 *
 * @level 4
 */
class Fibonacci {
    companion object {
        /**
         * Never use it !!
         */
        fun getNSimple(n: Int): Int {
            if (n <= 2) {
                return 1
            }
            return getNSimple(n - 1) + getNSimple(n - 2)
        }

        fun get(n: Int): Int {
            if (n <= 2) {
                return 1
            }
            return 0
        }

    }
}


fun main() {
    println(Fibonacci.getNSimple(100))
}
