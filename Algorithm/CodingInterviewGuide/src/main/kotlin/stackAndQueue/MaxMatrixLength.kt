package stackAndQueue

import kotlin.math.max

/**
 * @content 求最大矩阵的大小。 1 1 1 0 ->3 <br>
 *     1 0 1 1
 *     1 1 1 1
 *     1 1 1 0 -> 6
 * @require 矩阵的大小为（N*M），时间复杂度要求为ON（N*M）
 *
 * @level 3星
 */
class MaxMatrixLength {
    companion object {
        fun getMaxMatrixLength(matrix: ArrayList<ArrayList<Int>>): Int {
            if (matrix.size == 0 || matrix[0].size == 0) {
                return 0
            }
            var maxLength = 0

            var height = Array(matrix[0].size) {0}
            for (i in 0 until matrix.size) {
                for (j in 0 until matrix[i].size) {
                    if (matrix[i][j] == 0) {
                        height[j] = 0
                    } else {
                        height[j] = height[j] + 1
                    }
                    maxLength = max(maxLength(height), maxLength)
                }
            }

            return maxLength
        }

        private fun maxLength(height: Array<Int>): Int {
            var maxArea = 0;
            var stack = ArrayDeque<Int>()
            for ((i, v) in height.withIndex()) {
                while (!stack.isEmpty()  && height[i] <= height[stack.last()]) {
                    var j = stack.removeLast()
                    var k = if (stack.isEmpty()) -1 else stack.last()
                    var curArea = (i - k - 1) * height[j]
                    maxArea = max(maxArea, curArea)
                }
                stack.add(i)
            }
            while (!stack.isEmpty()) {
                var j = stack.removeLast()
                var k = if (stack.isEmpty()) -1 else stack.last()
                var curArea = (height.size - k - 1) * height[j]
                maxArea = max(maxArea, curArea)
            }

            return maxArea
        }
    }
}

fun main() {
    var row1 = arrayListOf(1, 0, 1, 1)
    var row2 = arrayListOf(1, 1, 1, 0)
    var row3 = arrayListOf(1, 1, 1, 0)
    var row4 = arrayListOf(1, 0, 1, 1)
    var matrix = arrayListOf(row1, row2, row3, row4)

    println(matrix)
    println(MaxMatrixLength.getMaxMatrixLength(matrix))
}
