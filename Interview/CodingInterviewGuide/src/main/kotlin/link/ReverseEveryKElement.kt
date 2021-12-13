package link

import struct.Node

/**
 * @content reverse every k element in a linked list, if remain elements are less than k, don't reverse them.
 * for example: 1->2->3->4->5->6->7->8 reverse by k=3 , turn to 3->2->1->6->5->4->7->8
 *
 * @level 2
 */
class ReverseEveryKElement {
    /**
     * help with a stack.
     */
    fun reverseByK(head: Node, k: Int): Node {
        if (k == 1) {
            return head
        }

        var stack = ArrayDeque<Node>()

        var cur: Node? = head
        var n = 0
        var newHead = head
        // stack first k element, if element count is less than k, don't do anything, and return original linkedlist.
        for (i in 0 until k) {
            stack.add(cur!!)
            if (cur.next != null) {
                cur = cur.next!!
            } else {
                return head
            }
        }
        newHead = stack.removeLast()

        var linker = newHead
        while (stack.isNotEmpty()) {
            linker.next = stack.removeLast()
            linker = linker.next!!
        }
        n = 0

        var beginNode = cur
        while (cur != null) {
            stack.add(cur)
            n++
            cur = cur.next
            if (n >= k) {
                beginNode = cur
                while (stack.isNotEmpty()) {
                    linker.next = stack.removeLast()
                    linker = linker.next!!
                    n--
                }
            }
        }
        linker.next = beginNode

        return newHead
    }
}

fun main() {
    var arr = Node.init(arrayListOf(1, 2, 3, 4, 5, 6, 7, 8))
    println(arr)

    var reverse = ReverseEveryKElement()
    println(reverse.reverseByK(arr, 3))

}
