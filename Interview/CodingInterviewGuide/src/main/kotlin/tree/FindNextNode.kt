package tree

class TreeNode(var value: Int, var leftNode: TreeNode? = null, var rightNode: TreeNode? = null, var parent: TreeNode? = null) {
    override fun toString(): String {
        var left = if (leftNode != null) leftNode!!.value.toString() else ""
        var right = if (rightNode != null) rightNode!!.value.toString() else ""
        var parent = if (parent != null) parent!!.value.toString() else ""

        return "value: $value, left: $left, right: $right, parent: $parent"
    }
}

/**
 * @content find next node in middle search
 *
 * @level 2
 */
class FindNextNode {
    companion object {
        fun getNextNode(node: TreeNode): TreeNode? {
            return if (node.rightNode != null) {
                getLeftMost(node.rightNode)
            } else {
                var parent = node.parent
                var cur = node
                while (parent!= null && parent.leftNode != cur) {
                    cur = parent
                    parent = parent.parent
                }
                return parent
            }
        }

        private fun getLeftMost(node: TreeNode?): TreeNode? {
            if (node == null) {
                return node
            }
            var cur = node.leftNode
            while (cur != null) {
                cur = cur.leftNode
            }
            return cur
        }
    }
}
fun main() {
    var treeNode1= TreeNode(1)
    var treeNode2= TreeNode(2)
    var treeNode3= TreeNode(3)
    var treeNode4= TreeNode(4)
    var treeNode5= TreeNode(5)
    var treeNode6= TreeNode(6)
    var treeNode7= TreeNode(7)
    var treeNode8= TreeNode(8)
    var treeNode9= TreeNode(9)
    var treeNode10= TreeNode(10)

    treeNode6.leftNode = treeNode3
    treeNode6.rightNode = treeNode9
    treeNode3.leftNode = treeNode1
    treeNode3.rightNode = treeNode4
    treeNode3.parent = treeNode6
    treeNode9.leftNode = treeNode8
    treeNode9.rightNode = treeNode10
    treeNode9.parent = treeNode6
    treeNode1.rightNode = treeNode2
    treeNode1.parent = treeNode3
    treeNode4.parent = treeNode3
    treeNode4.rightNode = treeNode5
    treeNode8.leftNode=treeNode7
    treeNode8.parent = treeNode9
    treeNode10.parent = treeNode9
    treeNode2.parent = treeNode1
    treeNode5.parent = treeNode4
    treeNode7.parent = treeNode8

    println(FindNextNode.getNextNode(treeNode2))
    println(FindNextNode.getNextNode(treeNode7))
}
