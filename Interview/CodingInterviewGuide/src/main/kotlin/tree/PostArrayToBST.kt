package tree

import struct.TreeNode

/**
 * @content check an array is a post ordered bst tree, and revert it to tree
 *
 * @level 1
 */
class PostArrayToBST {
    companion object {
        fun check(arr: ArrayList<Int>): Boolean {
            if (arr.isEmpty()) {
                return false
            }
            return check(arr, 0, arr.size - 1);
        }

        private fun check(arr: ArrayList<Int>, beginIndex: Int, endIndex: Int): Boolean {
            if (beginIndex == endIndex) {
                return true
            }
            var leftEnd = -1
            var rightBegin = endIndex
            for (i in beginIndex until endIndex) {
                if (arr[i] < arr[endIndex]) {
                    leftEnd = i
                } else {
                    rightBegin = if (rightBegin == endIndex) i else rightBegin
                }
            }
            if (leftEnd == -1 || rightBegin == endIndex) {
                return check(arr, beginIndex, endIndex - 1)
            }
            if (leftEnd != rightBegin - 1) {
                return false
            }
            return check(arr, beginIndex, leftEnd) && check(arr, rightBegin, endIndex - 1)
        }

        fun revertToTree(arr: ArrayList<Int>): TreeNode {
            if (arr.isEmpty()) {
                throw IllegalArgumentException("arr size should at least 1!!")
            }
            return revert(arr, 0, arr.size - 1)!!
        }

        private fun revert(arr: ArrayList<Int>, beginIndex: Int, endIndex: Int): TreeNode? {
            if (beginIndex > endIndex) {
                return null
            }
            var head = TreeNode(arr[endIndex])
            var leftEnd = -1
            var rightBegin = endIndex
            for (i in beginIndex until endIndex) {
                if (arr[i] < arr[endIndex]) {
                    leftEnd = i
                } else { // if the arr is actually post order
                    rightBegin = if (rightBegin == endIndex) i else rightBegin
                }
            }
            head.leftNode = revert(arr, beginIndex, leftEnd)
            head.rightNode = revert(arr, rightBegin, endIndex - 1)

            return head
        }

        fun isCBT(head: TreeNode): Boolean {
            var queue = ArrayDeque<TreeNode>()
            var isLeaf = false
            var leftNode: TreeNode? = null
            var rightNode: TreeNode? = null
            queue.add(head)
            while (!queue.isEmpty()) {
                var cur = queue.removeLast()
                leftNode = cur.leftNode
                rightNode = cur.rightNode
                if ((isLeaf && (leftNode != null || rightNode != null)) || (leftNode == null) && (rightNode != null)) {
                    return false
                }
                if (leftNode != null) {
                    queue.add(leftNode)
                }
                if (rightNode != null) {
                    queue.add(rightNode)
                } else {
                    isLeaf = true
                }
            }
            return true
        }
    }

}

fun main() {
    var arr = arrayListOf(2, 1, 3, 6, 5, 7, 4)
    println(PostArrayToBST.check(arr))

    var head = PostArrayToBST.revertToTree(arr)
    println(MorrisRetrieve.last(head))

    println(PostArrayToBST.isCBT(head))
}
