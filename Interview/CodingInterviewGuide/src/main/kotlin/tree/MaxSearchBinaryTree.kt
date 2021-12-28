package tree

import struct.TreeNode
import java.lang.Integer.min
import java.lang.Integer.max

/**
 * @content find max nodes count binary search tree in a tree
 *
 * @level 2
 */
class MaxSearchBinaryTree {
    companion object {
        fun findBiggestSubBST(head: TreeNode): TreeNode {
            var record = arrayListOf(0, Int.MAX_VALUE, Int.MIN_VALUE)
            return lastOrderSearch(head, record)!!
        }

        private fun lastOrderSearch(head: TreeNode?, record: ArrayList<Int>): TreeNode? {
            if (head == null) {
                record[0] = 0
                record[1] = Int.MAX_VALUE
                record[2] = Int.MIN_VALUE
                return null
            }
            var value = head.value
            var leftNode = head.leftNode
            var rightNode = head.rightNode
            var lBst = lastOrderSearch(leftNode, record)
            var lSize = record[0]
            var lMin = record[1]
            var lMax = record[2]
            var rBst = lastOrderSearch(rightNode, record)
            var rSize = record[0]
            var rMin = record[1]
            var rMax = record[2]
            record[1] = min(lMin, value)
            record[2] = max(rMax, value)
            if (leftNode == lBst && rightNode == rBst && value in (lMax + 1) until rMin) {
                record[0] = lSize + rSize + 1

                return head
            }
            record[0] = max(lSize, rSize)
            return  if (lSize > rSize) lBst else rBst
        }
    }
}

fun main() {
    var head = TreeSerialization.deserialization("6,1,12,0,3,10,13,#,#,#,#,4,14,20,16,2,5,11,15")
    MorrisRetrieve.pre(head)

    println(MaxSearchBinaryTree.findBiggestSubBST(head))
}
