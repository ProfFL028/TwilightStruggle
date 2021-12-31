package tree

import struct.TreeNode
import kotlin.math.max

/**
 * @content find max sum  of a tree path
 */
class FindPathOfMaxSum {
    companion object {
        fun findMaxSum(head: TreeNode): Int {
            var map = HashMap<TreeNode, Array<Int>>()
            return lastOrderSearch(head, map)
        }

        private fun lastOrderSearch(head: TreeNode?, map: HashMap<TreeNode, Array<Int>>): Int {
            if (head == null) {
                return 0
            }
            lastOrderSearch(head.leftNode, map)
            lastOrderSearch(head.rightNode, map)
            var lMap = map[head.leftNode]
            var rMap = map[head.rightNode]
            var maxLMap = if (lMap == null) 0 else max(lMap[0], lMap[1])
            var maxRMap = if (rMap == null) 0 else max(rMap[0], rMap[1])
            map.remove(head.leftNode)
            map.remove(head.rightNode)
            map[head] = arrayOf(maxLMap + head.value, maxRMap + head.value)

            return if (maxLMap > maxRMap) maxLMap + head.value else maxRMap + head.value
        }
    }
}

fun main() {
    var head = TreeSerialization.deserialization("6,1,12,0,3,10,13,#,#,#,#,4,14,20,16,2,5,11,15")
    MorrisRetrieve.pre(head)

    print(FindPathOfMaxSum.findMaxSum(head))
}
