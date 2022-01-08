package tree

import struct.TreeNode

/**
 * @content generate a balance binary search tree.
 *
 * @level 1
 */
class GenerateTree {
    companion object {
        fun createFrom(arr: ArrayList<Int>): TreeNode {
            if (arr.isEmpty()) {
                throw IllegalArgumentException("arr should not be empty")
            }

            return create(arr, 0, arr.size - 1)!!
        }

        private fun create(arr: ArrayList<Int>, beginIndex: Int, endIndex: Int): TreeNode? {
            if (beginIndex > endIndex) {
                return null
            }
            var mid = (beginIndex + endIndex) / 2
            var head = TreeNode(mid)
            head.leftNode = create(arr, beginIndex, mid - 1)
            head.rightNode = create(arr, mid + 1, endIndex)
            return head
        }
    }
}

fun main() {
    var arr = arrayListOf(1,2,3,4,5,6,7,8, 9, 10)
    var head = GenerateTree.createFrom(arr)
    println(MorrisRetrieve.middle(head))
    println(MorrisRetrieve.pre(head))
}
