package tree

import struct.TreeNode

/**
 * @content check if tree2 in tree1.
 *
 * @level 1
 */
class TreeTopologyContains {
    companion object {
        fun contains(tree1: TreeNode?, tree2: TreeNode): Boolean {
            if (tree1 == null) {
                return false
            }
            return check(tree1, tree2) || contains(tree1.leftNode, tree2) || contains(tree1.rightNode, tree2)
        }

        private fun check(tree1: TreeNode?, tree2: TreeNode?): Boolean {
            if (tree2 == null) {
                return true
            }
            if (tree1 == null || tree1.value != tree2.value) {
                return false
            }

            return check(tree1.leftNode, tree2.leftNode) && check(tree1.rightNode, tree2.rightNode)
        }
    }
}

fun main() {
    var head = TreeSerialization.deserialization("6,1,12,0,3,10,13,#,#,#,#,4,14,20,16,2,5,11,15")
    MorrisRetrieve.pre(head)
    var subTree = TreeSerialization.deserialization("10,4,14,2,5,11,#")
    println(TreeTopologyContains.contains(head, subTree))

    var subTree2 = TreeSerialization.deserialization("10,4,14,2,5,15,#")
    println(TreeTopologyContains.contains(head, subTree2))
}
