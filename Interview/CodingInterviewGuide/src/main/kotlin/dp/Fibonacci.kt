package dp

import struct.Matrix

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
            var matrix =  Matrix(2, 2, "1,1,1,0")
            var matrixN = matrix.pow(n)
            return matrixN.datas[0][0] + matrixN.datas[0][1]
        }

    }
}


fun main() {
    println(Fibonacci.get(100))
}
