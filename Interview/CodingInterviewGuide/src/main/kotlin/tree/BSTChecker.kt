package tree

import struct.TreeNode

/**
 * @content check if a tree is binary search tree, check if a tree is complete binary tree
 *
 * @level 1
 */
class BSTChecker {
    companion object {
        fun checkBST(head: TreeNode?): Boolean {
            if (head == null) {
                return true
            }
            var isBST = true
            var pre: TreeNode? = null
            var cur1: TreeNode? = head
            var cur2: TreeNode? = null
            while (cur1 != null) {
                cur2 = cur1.leftNode
                if (cur2 != null) {
                    while (cur2!!.rightNode != null && cur2.rightNode != cur1) {
                        cur2 = cur2.rightNode
                    }
                    if (cur2.rightNode == null) {
                        cur2.rightNode = cur1
                        cur1 = cur1.leftNode
                        continue
                    } else {
                        cur2.rightNode = null
                    }
                }
                if (pre != null && pre.value > cur1.value)
                    isBST = false
                pre = cur1
                cur1 = cur1.rightNode
            }

            return isBST
        }

        fun check2(head: TreeNode): Boolean {
            var queue = ArrayDeque<TreeNode>()
            queue.add(head)
            var isBST = true
            var preValue = Int.MIN_VALUE
            while (!queue.isEmpty()) {
                var cur = queue.last()
                if (cur.leftNode != null) {
                    queue.add(cur.leftNode!!)
                    continue
                } else {
                    if (preValue < cur.value) {
                        preValue = cur.value
                        queue.removeLast()
                        if (cur.rightNode != null) {
                            queue.add(cur.rightNode!!)
                        }
                    } else {
                        return false
                    }
                }
            }

            return isBST
        }

    }
}

fun main() {
    var head = TreeSerialization.deserialization("6,1,12,0,3,10,13,#,#,#,#,4,14,9,16,2,5,11,15")
    MorrisRetrieve.middle(head)
    println(BSTChecker.check2(head))
}
