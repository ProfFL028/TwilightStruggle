import java.util.*

fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val numCounts = input.nextInt()
        val increaseVector = Array(200001) { 0 }
        val decreaseVector = Array(200001) { 0 }
        var increaseCount = 0
        var decreaseCount = 0
        for (i in 0 until numCounts) {
            val progress = input.nextInt()

            if (increaseVector[progress] == 1) {
                if (decreaseVector[progress] == 1) {
                    println("NO")
                    return
                }
                decreaseVector[progress] = 1
                decreaseCount++
            } else {
                increaseVector[progress] = 1
                increaseCount++
            }

        }
        println("YES")
        println(decreaseCount)
        for (i in decreaseVector.indices) {
            if (decreaseVector[i] == 1) {
                print("$i ")
            }
        }
        println()
        println(increaseCount)
        for (i in increaseVector.size - 1 downTo  0) {
            if (increaseVector[i] == 1) {
                print("$i ")
            }
        }
        println()
    }

    val input = Scanner(System.`in`)
    solve(input)
}
