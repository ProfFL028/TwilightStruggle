import java.io.FileInputStream
import java.util.*

fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val MAX = 150000
        val numCounts = input.nextInt()
        val numArr = Array(MAX + 1) { 0 }
        val bakArr = Array(MAX + 1) { 0 }
        var maxCount = 0
        for (i in 0 until numCounts) {
            val num = input.nextInt() - 1
            bakArr[num] = 1
            if (numArr[num] == 0) {
                numArr[num] = 1
                maxCount++
            } else {
                var k = num + 1
                while (k <= MAX && bakArr[k] == 1) {
                    k++
                }
                if (numArr[k] == 0) {
                    numArr[k] = 1
                    maxCount++
                } else {
                    k = num - 1
                    while (k >= 0 && bakArr[k] == 1) {
                        k--
                    }
                    if (k >= 0 && numArr[k] == 0) {
                        numArr[k] = 1
                        maxCount++
                    }
                }
            }
        }
        println(maxCount)
    }


//    val input = Scanner(System.`in`)
//    solve(input)
    val input =
        Scanner(FileInputStream("src/main/resources/boxer_data"))
    val testCase = input.nextInt()
    for (i in 0 until testCase) {
        solve(input)
    }
}
