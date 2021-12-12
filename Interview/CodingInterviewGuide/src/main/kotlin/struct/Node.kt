package struct

class Node(var value: Int, var next: Node? = null) {
    override fun toString(): String {
        var str = "$value->"
        var cur = this
        while (cur.next != null) {
            cur = cur.next!!
            str += "${cur.value}->"
        }

        return str.substring(0, str.length - 2)
    }

    companion object {
        /**
         * init an node list from array
         * 1,2,3,4,5 => 1->2->3->4->5
         */
        fun init(arr: ArrayList<Int>): Node? {
            if (arr.isEmpty()) {
                return null
            }

            var head: Node = Node(arr[0], null)
            var prev: Node = head
            for (i in 1 until arr.size) {
                var cur = Node(arr[i], null)
                prev.next = cur
                prev = cur
            }

            return head
        }

        /**
         * join an array of nullable nodes formatted in head and end pairs: [h1, e1, h2, e2.... hn, en]
         * return first not null Node.
         */
        fun join(headEndArray: Array<Node?>): Node? {
            var len = headEndArray.size
            if (len % 2 != 0) {
                throw IllegalArgumentException("Invalid array")
            }
            var newHead = headEndArray[len - 2]
            for (i in len - 4 downTo 0 step 2) {
                if (headEndArray[i] != null) {
                    headEndArray[i+1]!!.next = newHead
                    newHead = headEndArray[i]
                }
            }
            return newHead
        }
    }
}

fun main() {
    var nodeList = Node.init(arrayListOf(9, 4, 5, 3, 3, 0, 1))
    print(nodeList)
}
