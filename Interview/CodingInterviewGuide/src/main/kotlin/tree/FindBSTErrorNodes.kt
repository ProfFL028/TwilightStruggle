package tree

import struct.TreeNode


/**
 * @content find two error nodes in a bst tree, and swap these two nodes(don't swap value)
 *
 * @level 4
 */
class FindBSTErrorNodes {
    companion object {
        fun find(head: TreeNode): ArrayList<TreeNode?> {
            var errNodes = arrayListOf<TreeNode?>(null, null)

            var stack = ArrayDeque<TreeNode>()
            var pre: TreeNode? = null
            var cur: TreeNode? = head

            var findCount = 0
            while (!stack.isEmpty() || cur != null) {
                if (cur != null) {
                    stack.add(cur)
                    cur = cur.leftNode
                } else {
                    cur = stack.removeLast()
                    if (pre != null && pre.value > head.value) {
                        errNodes[0] = errNodes[0] ?: pre
                        errNodes[1] = cur
                        findCount += 1
                        if (findCount >= 2) {
                            return errNodes
                        }
                    }
                    pre = cur
                    cur = cur.rightNode
                }
            }

            return errNodes
        }

        fun findParent(head: TreeNode, node: TreeNode?): TreeNode? {
            if (node == null) {
                return null
            }

            var stack = ArrayDeque<TreeNode>()
            var cur: TreeNode? = head
            while (stack != null || cur != null) {
                if (cur != null) {
                    stack.add(cur)
                    cur = cur.leftNode
                } else {
                    cur = stack.removeLast()
                    if (cur.leftNode == node || cur.rightNode == node)
                        return cur
                    cur = cur.rightNode
                }
            }

            return null
        }

        fun swapTwoNode(head: TreeNode, node1: TreeNode, node2: TreeNode): TreeNode {
            var node1Parent = findParent(head, node1)
            var node1Left = node1.leftNode
            var node1Right = node1.rightNode
            var node2Parent = findParent(head, node2)
            var node2Left = node2.leftNode
            var node2Right = node2.rightNode

            // in case node1 is the head of a binary search tree
            when {
                node1 == head -> {
                    node1.leftNode = node2Left
                    node1.rightNode = node2Right
                    when {
                        node1.leftNode == node2 -> { // it should never be happen in swapped binary search tree
                            node2.leftNode = node1
                            node2.rightNode = node1Right
                        }
                        node1.rightNode == node2 -> {
                            node2.leftNode = node1Left
                            node2.rightNode = node1
                        }
                        else -> {
                            node2.leftNode = node1Left
                            node2.rightNode = node1Left
                            if (node2Parent!!.leftNode == node2) {
                                node2Parent!!.leftNode = node1
                            } else {
                                node2Parent!!.rightNode = node1
                            }
                        }
                    }
                    return node2
                }
                node2 == head -> {
                    node2.leftNode = node1Left
                    node2.rightNode = node1Right
                    when {
                        node2.leftNode == node1 -> { // it should never be happen in swapped binary search tree
                            node1.leftNode = node2
                            node1.rightNode = node2Right
                        }
                        node2.rightNode == node1 -> {
                            node1.leftNode = node2Left
                            node1.rightNode = node2
                        }
                        else -> {
                            node1.leftNode = node2Left
                            node1.rightNode = node2Left
                            if (node1Parent!!.leftNode == node1) {
                                node1Parent!!.leftNode = node2
                            } else {
                                node1Parent!!.rightNode = node2
                            }
                        }
                    }
                    return node1
                }
                else -> {
                    when {
                        node1 == node2Parent -> {
                            if (node1Parent!!.leftNode == node1) {
                                node1Parent.leftNode = node2
                            } else {
                                node1Parent.rightNode = node2
                            }
                            node1.leftNode = node2.leftNode
                            node1.rightNode = node2.rightNode
                            if (node2Parent.leftNode == node2) { // it should never be happen in swapped binary search tree
                                node2.leftNode = node1
                                node2.rightNode = node1Right
                            } else {
                                node2.leftNode = node1.leftNode
                                node2.rightNode = node1
                            }
                        }
                        node1Parent == node2 -> {
                            if (node2Parent!!.leftNode == node2) {
                                node2Parent.leftNode = node1
                            } else {
                                node2Parent.rightNode = node1
                            }
                            node2.leftNode = node1.leftNode
                            node2.rightNode = node1.rightNode
                            if (node1Parent.leftNode == node1) { // it should never be happen in swapped binary search tree
                                node1.leftNode = node2
                                node1.rightNode = node2Right
                            } else {
                                node1.leftNode = node2.leftNode
                                node1.rightNode = node2
                            }
                        }
                        else -> {
                            node1.leftNode = node2Left
                            node1.rightNode = node2Right
                            node2.leftNode = node1Left
                            node2.rightNode = node1Right
                            if (node1Parent!!.leftNode == node1) {
                                node1Parent.leftNode = node2
                            } else {
                                node1Parent.rightNode = node2
                            }
                            if (node2Parent!!.leftNode == node2) {
                                node2Parent.leftNode = node1
                            } else {
                                node2Parent.rightNode = node1
                            }
                        }
                    }
                }
            }

            return head
        }
    }
}


fun main() {
    var head = TreeSerialization.deserialization("3,5,4,1,#,#,2")
    MorrisRetrieve.pre(head)
    var errNodes = FindBSTErrorNodes.find(head)
    println(errNodes[0])
    println(errNodes[1])

    println(FindBSTErrorNodes.findParent(head, errNodes[0]))
    println(FindBSTErrorNodes.findParent(head, errNodes[1]))

    var newHead = FindBSTErrorNodes.swapTwoNode(head, errNodes[0]!!, errNodes[1]!!)
    println(TreeSerialization.serialization(newHead))
}
