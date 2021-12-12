package link

import java.util.*

/**
 * @content 打印两个有序链表中公共的部分
 *
 * @level 1星
 */
class PrintSameParts {
    companion object {
        fun printSameParts(arr1: LinkedList<Int>, arr2:LinkedList<Int>) {
            var curr1 = arr1.iterator()
            var curr2 = arr2.iterator()

            var val1 = Int.MIN_VALUE
            var val2 = Int.MIN_VALUE

            while (curr1.hasNext() && curr2.hasNext()) {
                when {
                    val1 < val2 -> {
                        val1 = curr1.next()
                    }
                    val1 > val2 -> {
                        val2 = curr2.next()
                    }
                    else -> {
                        if (val1 != Int.MIN_VALUE)
                            println ("$val1 exists in both curr1 and curr2")
                        val1 = curr1.next()
                        val2 = curr2.next()
                    }
                }
            }
        }
    }
}

fun main() {
    var arr1 = LinkedList<Int>()
    arr1.add(1)
    arr1.add(2)
    arr1.add(3)
    arr1.add(4)
    arr1.add(5)
    arr1.add(6)
    var arr2 = LinkedList<Int>()
    arr2.add(1)
    arr2.add(4)
    arr2.add(7)

    PrintSameParts.printSameParts(arr1, arr2)
}
