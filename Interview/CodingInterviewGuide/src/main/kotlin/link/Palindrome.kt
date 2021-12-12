package link

import struct.Node
import kotlin.collections.ArrayDeque

/**
 * @content check if a list is palindrome
 *
 *
 * @level 1星
 */
class Palindrome {
    fun isPalindrome(head: Node): Boolean {
        // if there's only one element in node, return true
        if (head.next == null)
            return true

        /**
         * find the middle+1 point in odd(1,2,3,4,5，6，7）-》speed1Point.value=5
         * find the n/2+1 point in even(12345678) -》speed1Point.value=5
         * using two different speed points which takes O(1) space and O(N) time
         */
        var speed1Point:Node? = head.next
        var speed2Point:Node? = head
        while (speed2Point!!.next != null && speed2Point!!.next!!.next !=null) {
            speed1Point = speed1Point!!.next
            speed2Point = speed2Point!!.next!!.next
        }

        // push right-half points to a stack
        var stack = ArrayDeque<Int>()
        while (speed1Point != null) {
            stack.add(speed1Point.value)
            speed1Point = speed1Point.next
        }

        // pop stack and check values one by one
        var cur: Node? = head
        while (!stack.isEmpty()) {
            if (cur!!.value == stack.removeLast()) {
                cur = cur!!.next
            } else {
                return false
            }
        }

        return true
    }

    /**
     * reverse right nodes and then check points, without stack.
     */
    fun isPalindrome2(head: Node): Boolean {
        // if there's only one element in node, return true
        if (head.next == null)
            return true

        /**
         * find the middle+1 point in odd(1,2,3,4,5，6，7）-》speed1Point.value=5
         * find the n/2+1 point in even(12345678) -》speed1Point.value=5
         * using two different speed points which takes O(1) space and O(N) time
         */
        var point1:Node? = head.next
        var point2:Node? = head
        while (point2!!.next != null && point2!!.next!!.next !=null) {
            point1 = point1!!.next
            point2 = point2!!.next!!.next
        }

        // set point2 = point1.next and point1.next = null
        // 123456-： 123null  point2=4
        point2 = point1!!.next
        point1!!.next = null
        var point3: Node? = null
        // reverse points
        while (point2 != null) {
            point3 = point2.next
            point2.next = point1
            point1 = point2
            point2 = point3
        }

        point3 = point1
        point2 = head
        var result = true
        // check is palindrome
        while (point1 != null && point2 != null) {
            if (point1.value != point2.value) {
                result = false
                break
            }
            point1 = point1.next
            point2 = point2.next
        }

        // restore points
        point1 = point3!!.next
        point3!!.next = null
        while (point1 != null) {
            point2 = point1.next
            point1.next = point3
            point3 = point1
            point1 = point2
        }

        return result
    }
}

fun main() {
    var palindraome = Palindrome()
    var node5 = Node(1)
    var node4 = Node(4, node5)
    var node3 = Node(3, node4)
    var node2 = Node(2, node3)
    var node1 = Node(1, node2)

    println(node1)
    println("is node1 palindraome? ${palindraome.isPalindrome(node1)}")
    println("is node1 palindraome2? ${palindraome.isPalindrome2(node1)}")
    println(node1)
}


