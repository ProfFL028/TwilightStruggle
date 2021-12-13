package link

import struct.Node

/**
 * @content delete nodes who's value is equal to given number.
 *
 * @level 1
 */
class DeleteByValue {
    fun deleteByValue(head: Node, deleteValue: Int): Node? {
        var newHead:Node? = head
        while (newHead != null && newHead.value == deleteValue) {
            newHead = newHead.next
        }
        if (newHead == null) {
            return newHead
        }
        var cur = newHead.next
        var prev:Node? = newHead

        while(cur != null) {
            cur = cur.next
            if (prev!!.next!!.value == deleteValue) {
                prev!!.next = cur
            } else {
                prev = prev.next
            }
        }

        return newHead
    }
}

fun main() {
    var arr = Node.init(arrayListOf(1,2,3,3,4,4,2,1,1))
    println(arr)
    var dep = DeleteByValue()
    var newHead = dep.deleteByValue(arr, 1)
    println(newHead)
}
