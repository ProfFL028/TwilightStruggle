import java.util.*

fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val numCounts = input.nextInt()
        val increaseVector = Array(200001) { 0 }
        val decreaseVector = Array(200001) { 0 }
        var increaseCount = 0
        var decreaseCount = 0
        for (i in 0 until numCounts) {
            val cur = input.nextInt()

            if (increaseVector[cur] == 1) {
                if (decreaseVector[cur] == 1) {
                    println("NO")
                    return
                }
                decreaseVector[cur] = 1
                decreaseCount++
            } else {
                increaseVector[cur] = 1
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
