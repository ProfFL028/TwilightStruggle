package stackAndQueue

/**
 * @question 设计一个有GetMin()函数的stack,要求只能使用stack
 *
 * @require pop, push, getMin 的时间复杂要求均为 O(1)
 * @require 只允许使用stack结构
 *
 * @level 1星
 */

class GetMinStack() {
    var stackData = ArrayDeque<Int>()
    var stackMin = ArrayDeque<Int>()

    /**
     * stackData 直接新增新的数据即可。stackMin则需要判断栈顶元素是否比newNumber大，如果大的话，则需要把newNumber插入到栈顶中
     */
    fun push(newNumber: Int) {
        stackData.add(newNumber)
        if (stackMin.isEmpty()) {
            stackMin.add(newNumber)
        } else if (this.getMin() >= newNumber) {
            stackMin.add(newNumber)
        }
    }

    /**
     * stackData直接弹出最上面的数据，stackMin则需要判断弹出的数据是否等于最小值，如果相等，则同样需要弹出最上面的值。
     */
    fun pop(): Int {
        var minValue = stackData.removeLast()
        if (minValue == this.getMin())
            stackMin.removeLast()
        return minValue
    }

    fun getMin(): Int {
        if (stackMin.isEmpty()) {
            throw RuntimeException("There's no data in the stack")
        }
        return stackMin.last()
    }
}

fun main() {
    var stack = GetMinStack()
    stack.push(5)
    stack.push(2)

    println("stack 5, 2 -> getMin -> " + stack.getMin())

    stack.push(1)
    stack.push(4)

    println("stack 5, 2, 1, 4 -> getMin -> " + stack.getMin())

    stack.pop()
    stack.pop()
    println("stack 5 2 -> getMin ->" + stack.getMin())

}

