import java.util.*
import kotlin.collections.ArrayDeque

fun deepCopy(array: ArrayList<Int>): ArrayList<Int> {
    val newArr = ArrayList<Int>()
    for (ele in array) {
        newArr.add(ele)
    }
    return newArr
}

class TreeNode(
    var max: Int = 200001,
    var min: Int = 0,
    var lefNode: TreeNode? = null,
    var rightNode: TreeNode? = null,
    var parent: TreeNode? = null
)

fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val numCount = input.nextInt()
        val nums = Array(numCount) { 0 }
        val result = Array(numCount) { 1 }
        var preMaxIdx = -1
        var maxIdx = 0
        var minIdx = -1

        var solvable = true
        nums[0] = input.nextInt()
        for (i in 1 until numCount) {
            val num = input.nextInt()
            nums[i] = num
            if (maxIdx == -1) {
                preMaxIdx = maxIdx
                maxIdx = i
            } else {
                if (num < nums[maxIdx]) {
                    preMaxIdx = maxIdx
                    maxIdx = i
                } else {
                    if (minIdx == -1 || (minIdx < maxIdx && nums[maxIdx] > nums[minIdx])) {
                        minIdx = maxIdx
                        result[minIdx] = 0
                        maxIdx = preMaxIdx
                        preMaxIdx = -1
                    }
                    if (maxIdx == -1) {
                        preMaxIdx = maxIdx
                        maxIdx = i
                    } else {
                        if (num < nums[maxIdx]) {
                            preMaxIdx = maxIdx
                            maxIdx = i
                        } else {
                            if (num > nums[minIdx]) {
                                minIdx = i
                                result[minIdx] = 0
                            } else {
                                solvable = false
                            }
                        }
                    }
                }
            }
        }
        if (solvable) {
            println("YES")

            for (i in result) {
                print("$i ")
            }
        } else {
            println("NO")
        }
    }

    val input = Scanner(System.`in`)

    solve(input)
}
