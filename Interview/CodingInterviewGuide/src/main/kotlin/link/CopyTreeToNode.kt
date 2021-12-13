package link

import struct.TreeNode
import struct.TwoNode

/**
 * @content copy a tree
 *
 * @level 2
 */
class CopyTreeToNode {
    fun copy(root: TreeNode): TwoNode {
        var head = TwoNode(root.value)
        var queue = ArrayDeque<TreeNode>()
        var queue2 = ArrayDeque<TwoNode>()

        queue.add(root)
        queue2.add(head)
        while (!queue.isEmpty()) {
            var cur = queue.removeFirst()
            var newCur = queue2.removeFirst()
            if (cur.leftNode != null) {
                queue.add(cur.leftNode!!)
                newCur.leftNode = TwoNode(cur.leftNode!!.value)
                queue2.add(newCur.leftNode!!)
            }
            if (cur.rightNode != null) {
                queue.add(cur.rightNode!!)
                newCur.rightNode = TwoNode(cur.rightNode!!.value)
                queue2.add(newCur.rightNode!!)
            }
        }

        return head
    }
}

fun main() {
    var treeNode = Array(11) { i -> TreeNode(i) }

    treeNode[6].leftNode = treeNode[4]
    treeNode[6].rightNode = treeNode[7]
    treeNode[4].leftNode = treeNode[2]
    treeNode[4].rightNode = treeNode[5]
    treeNode[2].leftNode = treeNode[1]
    treeNode[2].rightNode = treeNode[3]
    treeNode[7].rightNode = treeNode[9]
    treeNode[9].leftNode = treeNode[8]

    println(treeNode[6])

    var copyTree = CopyTreeToNode()
    println(copyTree.copy(treeNode[6]))
}



