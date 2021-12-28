package tree

import struct.TreeNode
import kotlin.math.max

/**
 * @content find max topology search binary tree nodes count.
 *
 * @level 2
 */
class MaxTopologyNodes {
    companion object {
        fun searchBstTopology1(head: TreeNode?): Int {
            if (head == null) {
                return 0
            }
            var max = maxTopology(head, head)
            max = max(max, searchBstTopology1(head.leftNode))
            max = max(max, searchBstTopology1(head.rightNode))
            return max
        }

        private fun maxTopology(head: TreeNode?, next: TreeNode?): Int {
            if (head != null && next != null && isBstTopology(head, next, next.value)) {
                return maxTopology(head, next.leftNode) + maxTopology(head, next.rightNode) + 1
            }

            return 0
        }

        private fun isBstTopology(head: TreeNode?, next: TreeNode?, value: Int): Boolean {
            if (head == null) {
                return false
            }
            if (next == head) {
                return true
            }
            return if (head.value > value) isBstTopology(head.leftNode, next, value) else isBstTopology(
                head.rightNode,
                next,
                value
            )
        }

        /**
         * a better way to search.
         * add a hashmap[node, (leftBstCount, rightBstCount)] for speed up search
         */
        fun searchBstTopology2(head: TreeNode): Int {
            var map = HashMap<TreeNode, ArrayList<Int>>()
            return lastOrderSearch(head, map)
        }

        private fun lastOrderSearch(head: TreeNode?, map: HashMap<TreeNode, ArrayList<Int>>): Int {
            if (head == null) {
                return 0
            }
            var leftCount = lastOrderSearch(head.leftNode, map)
            var rightCount = lastOrderSearch(head.rightNode, map)
            modifyMap(head.leftNode, head.value, map, true)
            modifyMap(head.rightNode, head.value, map, false)
            var leftNodeCounts = map[head.leftNode]
            var rightNodeCounts = map[head.rightNode]
            var lBstCount = if (leftNodeCounts == null) 0 else leftNodeCounts[0] + leftNodeCounts[1] + 1
            var rBstCount = if (rightNodeCounts == null) 0 else rightNodeCounts[0] + rightNodeCounts[1] + 1
            map[head] = arrayListOf(lBstCount, rBstCount)

            return max(lBstCount + rBstCount + 1, max(leftCount, rightCount))
        }

        private fun modifyMap(
            head: TreeNode?,
            value: Int,
            map: HashMap<TreeNode, ArrayList<Int>>,
            leftOrRight: Boolean
        ): Int {
            if (head == null || !map.containsKey(head)) {
                return 0
            }
            var bstCounts = map.getValue(head)
            if ((leftOrRight && head.value > value) || (!leftOrRight && head.value < value)) {
                map.remove(head)
                return bstCounts[0] + bstCounts[1] + 1
            } else {
                var minus = if (leftOrRight) modifyMap(head.rightNode, value, map, leftOrRight) else modifyMap(
                    head.leftNode,
                    value,
                    map,
                    leftOrRight
                )
                if (leftOrRight) {
                    bstCounts[1] = bstCounts[1] - minus
                } else {
                    bstCounts[0] = bstCounts[0] - minus
                }

                map[head] = bstCounts
                return minus
            }
        }
    }
}

fun main() {
    var head = TreeSerialization.deserialization("6,1,12,0,3,10,13,#,#,#,#,4,14,20,16,2,5,11,15")
    MorrisRetrieve.pre(head)

    println(MaxTopologyNodes.searchBstTopology1(head))
    println(MaxTopologyNodes.searchBstTopology2(head))
}
