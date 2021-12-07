package stackAndQueue

/**
 * @content 将 1，2，3，4，5 转置成 5 4 3 2 1
 *
 * @require 只能使用递归和栈
 *
 * @level 2星
 */
class ReverseStack {
    companion object {
        fun getAndRemoveLastElement(stack: ArrayDeque<Int>): Int {
            var result = stack.removeLast()
            if (stack.isEmpty()) {
                return result
            }

            var last = getAndRemoveLastElement(stack)
            stack.add(result)
            return last
        }

        fun reverse(stack: ArrayDeque<Int>) {
            if (stack.isEmpty())
                return
            var result = getAndRemoveLastElement(stack)
            reverse(stack)
            stack.add(result)
        }
    }

}

fun main(args: Array<String>) {
    var stack = ArrayDeque<Int>()
    stack.addAll(listOf(1, 2, 3, 4, 5))
    println("stack original: $stack")
    println("reverse output: " + ReverseStack.getAndRemoveLastElement(stack))


    ReverseStack.reverse(stack)
    println("stack reversed: $stack")
}
