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

    /**
     * return length of node no matter it has ring or not:
     * 1->2->3->4->5->6->7: 7
     * 1->2->3->4->5->6->7->1->2...: 7
     * 1->2->3->4->5->6->7->2->3...: 7
     *
     * add some logic to containsLoop logic to avoid loop through the linked list twice.
     */
    fun length(): Int {
        if (this.next == null) {
            return 1
        }
        if (this.next!!.next == null) {
            return 2
        }

        var n1 = this.next
        var n2 = this.next!!.next
        var result = 3
        while (n1 != n2) {
            if (n2!!.next != null && n2.next!!.next != null) {
                n2 = n2!!.next!!.next
                n1 = n1!!.next
            } else {
                if (n2!!.next != null) {
                    result += 1
                }
                return result
            }
            result += 2
        }
        n2 = this
        result = 1
        while (n1 != n2) {
            n1 = n1!!.next
            n2 = n2!!.next
            result++
        }
        n1 = n1!!.next
        while (n1 != n2) {
            n1 = n1!!.next
            result++
        }
        return result
    }

    fun getEndWithLength(): Pair<Node, Int> {
        var node:Node? = this
        var len = 1
        while (node!!.next != null) {
            node = node!!.next
            len += 1
        }
        return Pair(node, len)
    }

    /**
     * check if a linked list contains loop.
     */
    fun containsLoop(): Boolean {
        return this.meetNode() != null
    }

    /**
     * set n1 to the meet node and n2 to the head. suppose linked list have l nodes, and k loop nodes,
     * as they will meet after l-k steps, let n2 run l-k steps, n1 and n2 will meet again.
     */
    fun firstInLoopNode(): Node? {
        var n1: Node? = meetNode() ?: return null
        var n2: Node? = this
        while (n1 != n2) {
            n1 = n1!!.next
            n2 = n2!!.next
        }
        return n1
    }

    /**
     * if a linked list contains loop, using a node walks through the linked list at speed 1 and another node speed 2,
     * if will meet, then return the meet node.
     */
    private fun meetNode(): Node? {
        if (this.next == null || this.next!!.next == null) {
            return null
        }
        var n1: Node? = this.next
        var n2: Node? = this.next!!.next
        while (n1 != n2) {
            if (n2!!.next != null && n2.next!!.next != null) {
                n2 = n2!!.next!!.next
                n1 = n1!!.next
            } else {
                return n1
            }
        }
        return null
    }

    companion object {
        /**
         * init an node list from array
         * 1,2,3,4,5 => 1->2->3->4->5
         */
        fun init(arr: ArrayList<Int>): Node {
            if (arr.isEmpty()) {
                return Node(0)
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
                    headEndArray[i + 1]!!.next = newHead
                    newHead = headEndArray[i]
                }
            }
            return newHead
        }
    }
}

fun main() {
    var nodeList = Node.init(arrayListOf(9, 4, 5, 3, 3, 0, 1))
    println(nodeList)
    println(nodeList.length())

    nodeList.next!!.next!!.next!!.next!!.next!!.next!!.next = nodeList.next!!.next
    println(nodeList.length())
}
