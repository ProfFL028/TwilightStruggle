package tree

import struct.TreeNode
import kotlin.math.max

/**
 * @content given a number and head of a tree, find the maxlength of a path that their sum equals to the number.
 *
 * @level 2?
 */
class FindMaxLengthOfGivingSum {
    companion object {
        fun find(head: TreeNode, sum: Int): Int {
            var map = HashMap<Int, Int>()
            map[0] = 0
            return preOrderSearch(head, sum, 0, 1, 0, map)
        }

        private fun preOrderSearch(
            head: TreeNode?,
            sum: Int,
            preSum: Int,
            level: Int,
            maxLen: Int,
            sumMap: HashMap<Int, Int>
        ): Int {
            if (head == null) {
                return maxLen
            }
            var curSum = preSum + head.value
            if (!sumMap.containsKey(curSum)) {
                sumMap[curSum] = level
            }
            var newMax = maxLen
            if (sumMap.containsKey(curSum - sum)) {
                newMax = max(level - sumMap.getValue(curSum - sum), newMax)
            }
            newMax = preOrderSearch(head.leftNode, sum, curSum, level + 1, newMax, sumMap)
            newMax = preOrderSearch(head.rightNode, sum, curSum, level + 1, newMax, sumMap)

            return newMax
        }
    }
}

fun main() {
    var head = TreeSerialization.deserialization("-3, 3, -9, 1, 0, 2, 1, #, #, 1, 6,#")
    println(MorrisRetrieve.middle(head))
    println(FindMaxLengthOfGivingSum.find(head, 6))
    println(FindMaxLengthOfGivingSum.find(head, 2))
    println(FindMaxLengthOfGivingSum.find(head, -7))
    println(FindMaxLengthOfGivingSum.find(head, -99))
}
