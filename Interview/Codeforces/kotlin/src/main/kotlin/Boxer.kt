import java.io.FileInputStream
import java.util.*

fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val MAX = 150000
        val numCounts = input.nextInt()
        val reachedArr = Array(MAX + 1) { 0 }
        val realArr = Array(MAX + 1) { 0 }
        var maxCount = 0

        for (i in 0 until numCounts) {
            val num = input.nextInt() - 1
            realArr[num] = 1

            if (reachedArr[num] == 0) {
                reachedArr[num] = 1
                maxCount++
            } else {
                var j = num - 1
                while (j > 1 && realArr[j] == 1) {
                    j--
                }
                if (num > 1 && reachedArr[j] == 0) {
                    reachedArr[j] = 1
                    maxCount++
                } else {
                    j = num + 1
                    while (j < MAX && realArr[j] == 1) {
                        j++
                    }
                    if (reachedArr[j] == 0) {
                        reachedArr[j] = 1
                        maxCount++
                    }
                }
            }
        }

        println(maxCount)
    }


    val input = Scanner(System.`in`)
    solve(input)
//    val input =
//        Scanner(FileInputStream("src/main/resources/boxer_data"))
//    val testCase = input.nextInt()
//    for (i in 0 until testCase) {
//        solve(input)
//    }
}
