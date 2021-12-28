package tree

import struct.TreeNode

/**
 * @content Morris Retrieve a tree, extract space O(1)
 *
 * @level 4
 */
class MorrisRetrieve {
    companion object {
        fun middle(head: TreeNode) {
            var cur1: TreeNode? = head
            var cur2: TreeNode? = null

            while (cur1 != null) {
                cur2 = cur1.leftNode;
                if (cur2 != null) {
                    while (cur2!!.rightNode != null && cur1 != cur2.rightNode) {
                        cur2 = cur2!!.rightNode
                    }
                    if (cur2.rightNode == null) {
                        cur2.rightNode = cur1
                        cur1 = cur1.leftNode
                        continue
                    } else {
                        cur2.rightNode = null
                    }
                }
                print("${cur1.value}, ")
                cur1 = cur1.rightNode
            }
            println()
        }

        fun pre(head: TreeNode) {
            var cur1: TreeNode? = head
            var cur2: TreeNode? = null
            while (cur1 != null) {
                cur2 = cur1.leftNode
                if (cur2 != null) {
                    while (cur2!!.rightNode != null && cur2!!.rightNode != cur1) {
                        cur2 = cur2.rightNode
                    }
                    if (cur2.rightNode == null) {
                        cur2.rightNode = cur1
                        print("${cur1.value}, ")
                        cur1 = cur1.leftNode
                        continue
                    } else {
                        cur2.rightNode = null
                    }
                } else {
                    print("${cur1.value}, ")
                }
                cur1 = cur1.rightNode
            }
            println()
        }

        fun last(head: TreeNode) {
            var cur1: TreeNode? = head
            var cur2: TreeNode? = null

            while (cur1 != null) {
                cur2 = cur1.leftNode
                if (cur2 != null) {
                    while (cur2!!.rightNode != null && cur2.rightNode != cur1) {
                        cur2 = cur2!!.rightNode
                    }
                    if (cur2.rightNode == null) {
                        cur2.rightNode = cur1
                        cur1 = cur1.leftNode
                        continue
                    } else {
                        cur2.rightNode = null
                        printRight(cur1.leftNode)
                    }
                }
                cur1 = cur1.rightNode
            }
            printRight(head)
            println()
        }

        fun reverseRight(head: TreeNode?): TreeNode? {
            var root = head
            var next:TreeNode? = null
            var pre:TreeNode? = null
            while (root != null) {
                next = root.rightNode
                root.rightNode = pre
                pre = root
                root =next
            }
            return pre
        }

        fun printRight(head: TreeNode?) {
            var tail = reverseRight(head)
            var cur = tail
            while (cur != null) {
                print("${cur.value}, ")
                cur = cur.rightNode
            }
            reverseRight(tail)
        }
    }
}

fun main() {
    var head = TreeSerialization.deserialization("4,2,6,1,3,5,7")

    MorrisRetrieve.middle(head)
    println()
    MorrisRetrieve.pre(head)
    println()
    MorrisRetrieve.last(head)
}
