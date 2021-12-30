package tree

import struct.TreeNode
import tree.MorrisRetrieve
import tree.TreeSerialization
import kotlin.math.abs
import kotlin.math.max

/**
 * @content check if a tree is a balance binary tree
 *
 * @level 1
 */
class BalanceTree {
    companion object {
        var isBalance = true
        fun check(head: TreeNode): Boolean {
            isBalance = true
            getHeight(head, 1)
            return isBalance
        }
        private fun getHeight(head: TreeNode?, level: Int): Int {
            if (head == null) {
                return level
            }
            var lHeight = getHeight(head.leftNode, level + 1)
            if (!isBalance)
                return level
            var rHeight = getHeight(head.rightNode, level + 1)
            if (!isBalance)
                return level
            isBalance = abs(lHeight - rHeight) <= 1
            return max(lHeight, rHeight)
        }
    }
}

fun main() {
    var head = TreeSerialization.deserialization("-3, 3, -9, 1, 0, 2, 1, #, #, 1, 6,#")
    println(BalanceTree.check(head))

    head = TreeSerialization.deserialization("6,1,12,0,3,10,13,#,#,#,#,4,14,20,16,2,5,11,15")
    println(BalanceTree.check(head))
}
