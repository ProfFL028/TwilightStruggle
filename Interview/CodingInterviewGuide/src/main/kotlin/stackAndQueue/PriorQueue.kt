package stackAndQueue

interface PriorQueue<T : Comparable<T>> {
    fun top(): T?
    fun peek(): T?
    fun insert(ele: T)
    fun remove(ele: T)
    fun update(oldEle: T, newEle: T)
    fun size(): Int
}

data class ElementNode<T>(var value: T, var next: ElementNode<T>? = null)

class SortedArrayPQ<T : Comparable<T>> : PriorQueue<T> {
    override fun top(): T? {
        return if (this.counter > 0) {
            var result = head!!.value
            head = head!!.next
            this.counter--
            return result
        } else {
            null
        }
    }

    override fun peek(): T? {
        return if (this.counter > 0) {
            return head!!.value
        } else {
            null
        }
    }

    override fun insert(ele: T) {
        var cur = head
        var pre: ElementNode<T>? = null
        while (cur != null) {
            if (ele > cur.value) {
                val newNode = ElementNode(ele, cur)
                if (pre != null) {
                    pre.next = newNode
                } else {
                    head = newNode
                }
                break
            }
            pre = cur
            cur = cur.next
        }
        if (cur == null) {
            val newNode = ElementNode(ele, null)
            if (pre != null) {
                pre.next = newNode
            } else {
                head = newNode
            }
        }
        this.counter++
    }

    override fun remove(ele: T) {
        var cur = head
        var pre: ElementNode<T>? = null
        while (cur != null) {
            if (ele == cur.value) {
                pre!!.next = cur.next
                this.counter--
                break
            }
            pre = cur
            cur = cur.next
        }
    }

    override fun update(oldEle: T, newEle: T) {
        var cur = head
        while (cur != null) {
            if (oldEle == cur.value) {
                cur.value = newEle
                break
            }
            cur = cur.next
        }
    }

    override fun size(): Int {
        return this.counter
    }

    private var head: ElementNode<T>? = null
    private var counter: Int = 0
}

class UnsortedArrayPQ<T : Comparable<T>> : PriorQueue<T> {
    override fun top(): T? {
        var oldTop = topEle
        data.remove(topEle)
        topEle = findTop()
        return oldTop
    }

    override fun peek(): T? {
        return topEle
    }

    override fun insert(ele: T) {
        data.add(ele)
        updateTopEle(ele)
    }

    override fun remove(ele: T) {
        for (i in data.indices) {
            if (data[i] == ele) {
                data.removeAt(i)
                return
            }
        }
    }

    override fun update(oldEle: T, newEle: T) {
        for (i in data.indices) {
            if (data[i] == oldEle) {
                data[i] = newEle

                if (topEle == oldEle) {
                    topEle = findTop()
                }

                return
            }
        }
    }

    private fun findTop(): T? {
        if (data.size > 0) {
            var result = data[0]
            for (i in 1 until data.size) {
                if (data[i] > result)
                    result = data[i]
            }
            return result
        }
        return null
    }

    private fun updateTopEle(ele: T) {
        if (topEle == null) {
            topEle = ele
        } else {
            if (ele > topEle!!) {
                topEle = ele
            }
        }
    }

    override fun size(): Int {
        return data.size
    }

    private var data: MutableList<T> = mutableListOf()
    private var topEle: T? = null
}

class DArrayTreePQ<T: Comparable<T>>(dim: Int = 2) : PriorQueue<T> {
    var data: MutableList<T> = mutableListOf()

    override fun top(): T? {
        TODO("Not yet implemented")
    }

    override fun peek(): T? {
        TODO("Not yet implemented")
    }

    override fun insert(ele: T) {
        TODO("Not yet implemented")
    }

    override fun remove(ele: T) {
        TODO("Not yet implemented")
    }

    override fun update(oldEle: T, newEle: T) {
        TODO("Not yet implemented")
    }

    override fun size(): Int {
        return this.data.size
    }
}


data class BugInfo(var bugDetail: String, var priority: Short) : Comparable<BugInfo> {
    override fun compareTo(other: BugInfo): Int {
        return this.priority.compareTo(other.priority)
    }

    override fun toString(): String {
        return "Priority[ $priority ] -> $bugDetail"
    }
}

fun main() {
    val pq = SortedArrayPQ<BugInfo>()
    val bug0 = BugInfo("Page loads take 2+ seconds", 7)
    val bug1 = BugInfo("UI breaks on browser X", 9)
    val bug2 = BugInfo("Optional from field blocked when using browser X on Friday the 13th", 1)
    val bug3 = BugInfo("CSS style causes misalignment", 8)
    val bug4 = BugInfo("CSS style causes 1px misalignment on browser X", 5)

    pq.insert(bug0)
    pq.insert(bug1)
    pq.insert(bug2)
    pq.insert(bug3)
    pq.insert(bug4)

    println("----------- Sorted Array -----------")
    var curBug = pq.top()
    while (curBug != null) {
        println(curBug)
        curBug = pq.top()
    }

    println("----------- Unsorted Array -----------")
    val unsortPQ = UnsortedArrayPQ<BugInfo>()
    unsortPQ.insert(bug0)
    unsortPQ.insert(bug1)
    unsortPQ.insert(bug2)
    unsortPQ.insert(bug3)
    unsortPQ.insert(bug4)

    curBug = unsortPQ.top()
    while (curBug != null) {
        println(curBug)
        curBug = unsortPQ.top()
    }
}
