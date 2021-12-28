package tree

import struct.TreeNode
import java.lang.NumberFormatException

/**
 * @content Serialization and Deserialization a tree.
 *
 * @level 2
 */
class TreeSerialization {
    companion object {
        fun serialization(root: TreeNode): String {
            var result = ""
            var stack = ArrayDeque<TreeNode>()
            stack.add(root)
            result = result.plus(root.value).plus(",")

            while (!stack.isEmpty()) {
                var node = stack.removeFirst();
                result = if (node.leftNode != null) {
                    stack.add(node.leftNode!!)
                    result.plus(node.leftNode!!.value).plus(",")
                } else {
                    result.plus("#,")
                }

                result = if (node.rightNode != null) {
                    stack.add(node.rightNode!!)
                    result.plus(node.rightNode!!.value).plus(",")
                } else {
                    result.plus("#,")
                }
            }
            return result.dropLast(1)
        }

        fun deserialization(str: String): TreeNode {
            var values = str.split(",")

            var intValue = stoi(values[0]) ?: 0
            var root = TreeNode(intValue)

            var currentNode = root
            var stack = ArrayDeque<TreeNode>()

            var idx = 1
            while (idx < values.size) {
                var v = stoi(values[idx])

                if (v != null) {
                    currentNode.leftNode = TreeNode(v)
                    stack.add(currentNode.leftNode!!)
                }
                idx += 1
                if (idx < values.size) {
                    v = stoi(values[idx])
                    if (v != null) {
                        currentNode.rightNode = TreeNode(v)
                        stack.add(currentNode.rightNode!!)
                    }
                    currentNode = stack.removeFirst()
                    idx += 1
                }
            }
            return root
        }

        fun stoi(str: String): Int? {
            if (str.trim() == "#") {
                return null
            }

            return try {
                Integer.parseInt(str.trim())
            } catch (e: NumberFormatException) {
                null
            }

        }
    }

}

fun main() {
    var head = TreeSerialization.deserialization("1,2,3,4,#,#,5")
    println(head)
    println("${head.leftNode!!}, ${head.rightNode!!}")

    println(TreeSerialization.serialization(head))
}
