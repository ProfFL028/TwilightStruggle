package stackAndQueue

import java.lang.RuntimeException

/**
 * @content 给定一个数组和整数，求满足最大值减最小值小于或等于给定整数的子数组个数
 *
 * @require 时间复杂度要求为O(N)
 *
 * @level 3星
 */
class MaxMinSubArrayCount {
    companion object {
        fun getSubArrayCount(arr: ArrayList<Int>, threshold: Int): Int {
            if (threshold <= 0 || arr.isEmpty())
                throw RuntimeException("Threshold should be greater than 0")

            var stackMax = ArrayDeque<Int>()
            var stackMin = ArrayDeque<Int>()
            var totalCount = 0
            var i = 0
            var j = 0

            while (i < arr.size) {
                while (j < arr.size) {
                    while (!stackMin.isEmpty() && arr[stackMin.last()] >= arr[j])
                        stackMin.removeLast()
                    stackMin.add(j)
                    while (!stackMax.isEmpty() && arr[stackMax.last()] <= arr[j])
                        stackMax.removeLast()
                    stackMax.add(j)
                    if (arr[stackMax.first()] - arr[stackMin.first()] > threshold)
                        break
                    j++
                }
                if (stackMin.first() == i)
                    stackMin.removeFirst()
                if (stackMax.first() == i)
                    stackMax.removeFirst()
                println("i = $i, j = $j")
                totalCount += j - i
                i++
            }
            return totalCount
        }
    }
}

fun main() {
    var arr = arrayListOf(5, 4, 3, 1, 6, 2)
    println(MaxMinSubArrayCount.getSubArrayCount(arr, 1))
    println(MaxMinSubArrayCount.getSubArrayCount(arr, 2))
}
