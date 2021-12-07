package stackAndQueue

/**
 * @content 生成窗口最大值数组。 一个整型数组arr, 和一个窗口w, 窗口从最左边一个一个地滑向最右边，每滑过一个位置，取最大的整数。<br/>
 * 例如：[4,3,5,4,3,3,6,7]->[5,5,5,4,6,7]
 *
 * @Require 时间复杂度要求为O(N),而不是O(N*w)
 *
 * @level 2星
 */
class MaxArrayWindow {

    /**
     * 空间换时间,将最大值存储在一个双向链表(队列即可)中.
     * 当下一个元素比最大值要小的时候,把这个值存到双向链表中(因为最大值离开窗口后,这个值有可能会成为最大值),如果链表长度比窗口长度长,则移除第一个元素
     * 当下一个元素比最大值要大的时候,清空链表,并把最大值插入链表中(原链表中的元素不可能成为最大值)
     */
    fun getMaxArrayWindow(arr: ArrayList<Int>, window: Int): ArrayList<Int> {
        if (arr.size < 0 || window > arr.size)
            return arrayListOf()

        var result = arrayListOf<Int>()

        /**
         * 第一个窗口
         */
        var maxQueue = ArrayDeque<Int>()
        maxQueue.add(0)
        for (i in 1 until window) {
            if (arr[maxQueue.first()] <= arr[i]) {
                maxQueue.clear()
                maxQueue.add(i)
            } else {
                maxQueue.add(i)
            }
        }
        result.add(arr[maxQueue.first()])
        printArr(arr, 0, window, maxQueue, result)
        for (i in window until arr.size) {
            if (arr[maxQueue.first()] <= arr[i]) {
                maxQueue.clear()
                maxQueue.add(i)
                result.add(arr[i])
            } else {
                result.add(arr[maxQueue.first()])
                maxQueue.add(i)
                if (maxQueue.size >= window) {
                    maxQueue.removeFirst()
                }
            }

            printArr(arr, i-window+1, window, maxQueue, result)
        }

        return result
    }

    private fun printArr(arr: ArrayList<Int>, curPosition: Int, window: Int, maxQueue: ArrayDeque<Int>, result: ArrayList<Int>) {

        for (i in 0 until curPosition)
            print("${arr[i]} ")
        print("[")
        for (i in 0 until window)
            print("${arr[curPosition + i]} ")
        print("]")
        for (i in (curPosition+window) until arr.size)
            print("${arr[i]} ")

        println(" --- result: $result ------ maxQueue: $maxQueue")
    }
}

fun main() {
    var maw = MaxArrayWindow()
    var result = maw.getMaxArrayWindow(arrayListOf(4,3,5,4,3,2,1,3,6,7), 5)

    println(result)
}
