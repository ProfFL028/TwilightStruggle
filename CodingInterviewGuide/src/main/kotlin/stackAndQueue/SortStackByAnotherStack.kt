package stackAndQueue

/**
 * @content 用一个栈实现另一个栈的排序
 *
 * @require 只许申请一个栈，可以申请一个新变量，不能使用额外的数据结构
 *
 * @level 1星
 */
class SortStackByAnotherStack {
    companion object {
        fun sort(stack: ArrayDeque<Int>) {
            if (stack.isEmpty()) {
                return
            }

            val helpStack = ArrayDeque<Int>()
            // helpStack.add(stack.removeLast())

            while (!stack.isEmpty()) {
                val cur = stack.removeLast()
                while (!helpStack.isEmpty() && cur > helpStack.last()) {
                    stack.add(helpStack.removeLast())
                }
                helpStack.add(cur)
            }

            while (!helpStack.isEmpty()) {
                stack.add(helpStack.removeLast())
            }
        }
    }
}

fun main() {
    val stack = ArrayDeque(arrayListOf(4, 7, 3, 1, 6, 5, 2))
    SortStackByAnotherStack.sort(stack)
    print(stack)
}
