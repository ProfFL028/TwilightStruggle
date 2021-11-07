package stackAndQueue

/**
 * @content 构造数组的MaxTree <br>
 *     MaxTree定义如下：数组必须没有重复元素；MaxTree 必须是一棵二叉树，数组的每一个值对应一个二叉树节点。
 *     包括MaxTree树在内在其中的每一棵子驿上，值最大的节点都是树的头。
 *
 * @require 时间复杂度O(N)， 额外空间复杂度O(N)
 * @level 3星
 */
class ArrayToMaxTree {

    /**
     * 每一个数的父节点是它左边第一个比它大的数和它右边第一个比它大的数的较小者。
     * 如一个数左边和右边都没有比它大的数，则它做为头节点。
     */
    fun createMaxTree(arr: ArrayList<Int>): Node {
        // 初始化所有节点
        var nodes = ArrayList<Node>()
        for (i in 0 until arr.size) {
            nodes.add(Node(arr[i]))
        }

        // 找到节点左侧比它小的数值
        var stack = ArrayDeque<Node>()
        var lBigMap = HashMap<Node, Node?>()
        var rBigMap = HashMap<Node, Node?>()
        lBigMap[nodes[0]] = null
        stack.add(nodes[0])
        for (i in 1 until arr.size) {
            var curNode = nodes[i]
            while (lBigMap.isNotEmpty() && stack.isNotEmpty() && stack.last().value < curNode.value) {
                popStackAndSetMap(stack, lBigMap)
            }
            stack.add(curNode)
        }
        while (!stack.isEmpty())
            popStackAndSetMap(stack, lBigMap)

        // 找到节点右侧比它大的数值
        rBigMap[nodes[nodes.size - 1]] = null
        stack.add(nodes[nodes.size - 1])
        for (i in (arr.size - 2) downTo 0) {
            var curNode = nodes[i]
            while (rBigMap.isNotEmpty() && stack.isNotEmpty() && stack.last().value < curNode.value) {
                popStackAndSetMap(stack, rBigMap)
            }
            stack.add(curNode)
        }
        while (!stack.isEmpty())
            popStackAndSetMap(stack, rBigMap)

        var head = Node(0)
        for (i in 0 until arr.size) {
            var curNode = nodes[i]
            var left = lBigMap[curNode]
            var right = rBigMap[curNode]

            if (left == null && right == null) {
                head = curNode
            } else if (left != null) {
                if (left.left != null) {
                    left.right = curNode
                } else {
                    left.left = curNode
                }
            } else if (right != null) {
                if (right.left != null) {
                    right.right = curNode
                } else {
                    right.left = curNode
                }
            } else {
                var parent = right
                if (left?.value!! < right?.value!!)
                    parent = left
                if (parent?.left == null) {
                    parent?.left = curNode
                } else {
                    parent?.right = curNode
                }
            }
        }

        return head
    }

    private fun popStackAndSetMap(stack: ArrayDeque<Node>, map: HashMap<Node, Node?>) {
        var node = stack.removeLast()
        if (stack.isEmpty()) {
            map[node] = null
        } else {
            map[node] = stack.last()
        }
    }
}

class Node(var value: Int, var left: Node?=null, var right: Node?=null) {
    fun print() {
        var queue = ArrayDeque<Node>()
        queue.add(this)

        while (queue.isNotEmpty()) {
            var curNode = queue.removeFirst()
            print("${curNode.value} ")
            if (curNode.left != null) {
                queue.add(curNode.left!!)
            }
            if (curNode.right != null) {
                queue.add(curNode.right!!)
            }
            println()
        }

    }
}

fun main() {
    var arr = arrayListOf(3, 4, 5, 1, 2)
    var amt = ArrayToMaxTree()
    var head = amt.createMaxTree(arr)
    head.print()
}
