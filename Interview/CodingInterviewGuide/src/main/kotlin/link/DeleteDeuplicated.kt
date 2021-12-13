package link

import struct.Node

/**
 * @content delete duplicated values in a linked list: 123344211->1234
 *
 * @level 1
 */
class DeleteDuplicated {
    fun deleteDuplicated(head: Node) {
        var values = HashSet<Int>()

        var cur = head.next
        var prev:Node? = head
        values.add(head.value)
        while (cur != null) {
            var curValue = cur.value
            cur = cur.next

            if (values.contains(curValue)) {
                prev!!.next = cur
            } else {
                values.add(curValue)
                prev = prev!!.next
            }
        }
    }
}

fun main () {
    var arr = Node.init(arrayListOf(1,2,3,3,4,4,2,1,1))
    println(arr)
    var dep = DeleteDuplicated()
    dep.deleteDuplicated(arr)
    println(arr)
}
