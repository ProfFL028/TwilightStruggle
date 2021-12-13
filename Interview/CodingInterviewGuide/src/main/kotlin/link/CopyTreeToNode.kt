package link

import struct.TreeNode
import struct.TwoNode

class CopyTreeToNode {
    fun copy(root: TreeNode): TwoNode {
        var head = TwoNode(root.value)
        var stack = head

        return head
    }
}

fun main() {
    var treeNode = Array<TreeNode>(11) { i -> TreeNode(i) }

    treeNode[6].leftNode = treeNode[4]
    treeNode[6].rightNode = treeNode[7]
    treeNode[4].leftNode = treeNode[2]
    treeNode[4].rightNode = treeNode[5]
    treeNode[2].leftNode = treeNode[1]
    treeNode[2].rightNode = treeNode[3]
    treeNode[7].rightNode = treeNode[9]
    treeNode[9].leftNode = treeNode[8]

    println(treeNode[6])
}



