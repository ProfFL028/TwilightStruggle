import java.io.FileInputStream
import java.util.*

fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val MAX = 150000
        val numCounts = input.nextInt()
        val numArray = Array(MAX + 1) { 0 }
        val resultArray = Array(MAX + 1) { 0 }
        for (i in 0 until numCounts) {
            val num = input.nextInt() - 1
            if (num in 0..MAX) {
                numArray[num] += 1
            }
        }
        var maxCount = 0
        if (numArray[0] >= 1) {
            maxCount += 1
            numArray[0] -= 1
            resultArray[0] = 1
        }
        if (numArray[0] >= 1) {
            maxCount += 1
            numArray[0] -= 1
            resultArray[1] = 1
        }
        for (i in 1..MAX) {
            if (resultArray[i - 1] == 0 && numArray[i] >= 1) {
                maxCount++
                numArray[i] -= 1
                resultArray[i - 1] = 1
            }
            if (resultArray[i] == 0 && numArray[i] >= 1) {
                maxCount++
                numArray[i] -= 1
                resultArray[i] = 1
            }
            if (numArray[i] >= 1) {
                maxCount++
                numArray[i] -= 1
                resultArray[i + 1] = 1
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
