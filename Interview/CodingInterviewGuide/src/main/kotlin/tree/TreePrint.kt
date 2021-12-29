package tree

import struct.TreeNode

/**
 * @content Print by Level and zigzag print
 *
 * @level 3
 */
class TreePrint {
    companion object {
        fun printByLevel(head: TreeNode) {
            var deque = ArrayDeque<TreeNode>()
            deque.add(head)
            var last = head
            var nLast: TreeNode? = null
            var level = 1
            print("Level $level: ")
            while (!deque.isEmpty()) {
                var cur = deque.removeFirst()
                print("${cur.value} ")
                if (cur.leftNode != null) {
                    deque.add(cur.leftNode!!)
                    nLast = cur.leftNode
                }
                if (cur.rightNode != null) {
                    deque.add(cur.rightNode!!)
                    nLast = cur.rightNode
                }
                if (cur == last && !deque.isEmpty()) {
                    last = nLast!!
                    level += 1
                    print("\nLevel $level: ")
                }
            }

            println()
        }

        fun zigZagPrint(head: TreeNode) {
            var deque = ArrayDeque<TreeNode>()
            deque.add(head)
            var last: TreeNode? = head
            var nLast: TreeNode? = null
            var level = 1
            var lr = true
            printLevelInfo(level)
            while (!deque.isEmpty()) {
                var cur = if (!lr) deque.removeLast() else deque.removeFirst()
                print("${cur.value} ")
                if (lr) {
                    if (cur.leftNode != null) {
                        deque.addLast(cur.leftNode!!)
                        nLast = nLast ?: cur.leftNode
                    }
                    if (cur.rightNode != null) {
                        deque.addLast(cur.rightNode!!)
                        nLast = nLast ?: cur.rightNode
                    }
                } else {
                    if (cur.rightNode != null) {
                        deque.addFirst(cur.rightNode!!)
                        nLast = nLast ?: cur.rightNode
                    }
                    if (cur.leftNode != null) {
                        deque.addFirst(cur.leftNode!!)
                        nLast = nLast ?: cur.leftNode
                    }
                }
                if (cur == last && !deque.isEmpty()) {
                    last = nLast
                    level += 1
                    lr = !lr
                    nLast = null
                    printLevelInfo(level)
                }
             }
        }

        private fun printLevelInfo(level: Int) {
            if (level % 2 == 1) {
                print("\nlevel $level from left to right: ")
            } else {
                print("\nlevel $level from right to left: ")
            }
        }

    }
}

fun main() {
    var head = TreeSerialization.deserialization("6,1,12,0,3,10,13,#,#,#,#,4,14,20,16,2,5,11,15")
    MorrisRetrieve.pre(head)

    TreePrint.printByLevel(head)
    println()
    println()
    TreePrint.zigZagPrint(head)
}
