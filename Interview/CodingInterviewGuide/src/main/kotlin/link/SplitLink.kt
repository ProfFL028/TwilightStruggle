package link

import struct.Node

/**
 * @content given a linked list <9, 4, 3, 3, 5, 0, 1> and a pivot number <3>。
 * split the linked list to three parts，the left part are numbers that small than pivot, and the middle part are equals to pivot
 * and the right part are numbers bigger than pivot. For example <0,1,3,3,9,4,5>
 *
 * @level 2
 */
class SplitLink {
    fun splitLink(head: Node, pivot: Int): Node {
        var nodes: Array<Node?> = arrayOf(null, null, null, null, null, null)
        var curNode: Node? = head
        var nextNode: Node? = head

        while (curNode != null) {
            nextNode = curNode.next
            curNode.next = null
            var i = 0
            if (curNode.value > pivot) {
                i = 4
            } else if (curNode.value == pivot) {
                i = 2
            }
            if (nodes[i] == null) {
                nodes[i] = curNode
                nodes[i + 1] = curNode
            } else {
                nodes[i + 1]!!.next = curNode
                nodes[i + 1] = curNode
            }
            curNode = nextNode
        }

        return Node.join(nodes)!!
    }
}

fun main() {
    var head = Node.init(arrayListOf(9, 4,1, 5, 3, 0, 7, 3, 3, 1))!!
    var splitLink = SplitLink()

    println(head)
    println(splitLink.splitLink(head, 3))

}
