package link

import struct.NodeWithRandNode

/**
 * @content deep copy node with rand node
 *
 * @level 2
 */
class DeepCopyNodeWithRandNode {
    /**
     * using a hashmap for deep copy. generate all nodes and store them into a hash.
     * generate next and rand point by hashmap
     */
    fun deepCopy(head: NodeWithRandNode): NodeWithRandNode {
        var hash = HashMap<NodeWithRandNode, NodeWithRandNode>()

        var cur: NodeWithRandNode? = head
        while (cur != null) {
            hash[cur] = NodeWithRandNode(cur.value)
            cur = cur.next
        }

        cur = head
        while (cur != null) {
            hash.getValue(cur).next = hash[cur.next]
            hash.getValue(cur).rand = hash[cur.rand]
            cur = cur.next
        }

        return hash.getValue(head)
    }

    /**
     * deep copy node without extra data structure.
     *  1->2->3
     *  in first loop copy each node and insert it between nodes:
     *  1->1'->2->2'->3->3'
     *  duration the second loop, set rand point and reset next point.
     */
    fun deepCopy2(head: NodeWithRandNode): NodeWithRandNode {
        var cur: NodeWithRandNode? = head
        var next: NodeWithRandNode?
        while (cur != null) {
            next = cur.next
            cur.next = NodeWithRandNode(cur.value)
            cur.next!!.next = next
            cur = next
        }
        cur = head
        var newHead = head.next!!
        while (cur != null) {
            next = cur.next!!

            next.rand = when (cur.rand) {
                null -> null
                else -> cur.rand!!.next
            }
            cur.next = next.next
            if (cur.next != null) {
                next.next = cur.next!!.next
            }
            cur = cur.next

        }

        return newHead
    }
}

fun main() {
    var node1 = NodeWithRandNode(1)
    var node2 = NodeWithRandNode(2)
    var node3 = NodeWithRandNode(3)
    node1.next = node2
    node1.rand = node3
    node2.next = node3
    node3.rand = node1

    println(node1)
    println(node2)
    println(node3)

    var deepCopy = DeepCopyNodeWithRandNode()
    var deepCopy2 = deepCopy.deepCopy2(node1)
    println("after deep copied")
    println(deepCopy2)
    println(deepCopy2.next)
    println(deepCopy2.next!!.next)
}
