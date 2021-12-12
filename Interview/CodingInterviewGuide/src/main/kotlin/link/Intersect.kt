package link

import struct.Node
import kotlin.math.abs

/**
 * given two linked nodes, find their first intersected node if exists or null if they don't intersect.
 * @require time speed O(N+M), cost O(1)
 * @level 4
 */
class Intersect {
    fun intersect(node1: Node, node2: Node): Node? {
        var loop1 = node1.firstInLoopNode()
        var loop2 = node2.firstInLoopNode()
        if (loop1 == null && loop2 == null) {
            return this.noLoopIntersect(node1, node2)
        }
        if (loop1 != null && loop2 != null) {
            return this.bothLoopIntersect(node1, loop1, node2, loop2)
        }
        return null
    }

    /**
     * return first intersect node of two linked node who don't have loop in it.
     * if node1.end != node2.end. then they don't have intersect
     * if node1.end == node2.end. take len1 = len(node1) and len2 = len(node2)
     * let node1 go len1-len2(len1>len2) and they walk together. they will meet at the first node
     */
    private fun noLoopIntersect(node1: Node, node2: Node): Node? {
        var (cur1, len1) = node1.getEndWithLength()
        var (cur2, len2) = node2.getEndWithLength()

        if (cur1 != cur2) {
            return null
        }
        cur1 = if (len1 > len2) node1 else node2
        cur2 = if (cur1 == node1) cur2 else cur1
        var n = abs(len1 - len2)
        while (n != 0) {
            cur1 = cur1.next!!
            n--
        }
        while (cur1 != cur2) {
            cur1 = cur1.next!!
            cur2 = cur2.next!!
        }
        return cur1
    }

    /**
     *
     */
    private fun bothLoopIntersect(node1: Node, loop1: Node, node2: Node, loop2: Node): Node? {
        var cur1: Node? = null
        var cur2: Node? = null
        if (loop1 == loop2) {
            cur1 = node1
            cur2 = node2
            var n = 0
            while (cur1 != loop1) {
                n++
                cur1 = cur1!!.next
            }
            while (cur2 != loop2) {
                n--
                cur2 = cur2!!.next
            }
            cur1 = if (n > 0) node1 else node2
            cur2 = if (cur1 == node1) node2 else node1
            n = abs(n)
            while (n != 0) {
                cur1 = cur1!!.next
                n--
            }
            while (cur1 != cur2) {
                cur1 = cur1!!.next
                cur2 = cur2!!.next
            }
            return cur1
        } else {
            cur1 = loop1.next
            while (cur1 != loop1) {
                if (cur1 == loop2)
                    return loop1
                cur1 = cur1!!.next
            }
        }

        return null
    }
}
