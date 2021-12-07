package Link

import java.lang.RuntimeException

class Node(var value: Int, var next: Node?=null) {
    override fun toString(): String {
        var str = "$value->"
        var cur = this
        while (cur.next != null) {
            cur = cur.next!!
            str += "${cur.value}->"
        }

        return str.substring(0, str.length - 2)
    }
}

/**
 * @content delete last Kth element
 *
 * @level 1星
 */
class DeleteLastKthNode {
    companion object {
        fun deleteLastKthNode(head: Node, k: Int): Node? {
            if (k <= 1 || head == null)
                throw RuntimeException("k should be greater than 1")

            var cur = head.next
            var i = 1
            while (cur != null && i < k) {
                cur = cur.next
                i++
            }
            var result:Node? = head
            if (cur != null) {
                var kNode = cur
                cur = head
                while (kNode!!.next != null) {
                    kNode = kNode.next
                    cur = cur!!.next
                }
                result = cur!!.next
                cur.next = cur.next!!.next
            }

            return result
        }
    }
}

fun main() {
    var node5 = Node(5)
    var node4 = Node(4, node5)
    var node3 = Node(3, node4)
    var node2 = Node(2, node3)
    var node1 = Node(1, node2)

    println(node1)
    println(DeleteLastKthNode.deleteLastKthNode(node1, 2))
    println(node1)
}
