import java.util.*

// TODO: SPEED UP
fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val numCounts = input.nextInt()
        val increaseVector = Vector<Int>(numCounts / 2)
        val decreaseVector = Vector<Int>(numCounts / 2)

        for (i in 0 until numCounts) {
            val cur = input.nextInt()
            var inserted = false
            var isEq = false
            for (j in 0 until increaseVector.size) {
                if (cur < increaseVector[j]) {
                    increaseVector.insertElementAt(cur, j)
                    inserted = true
                    break
                } else if (cur == increaseVector[j]) {
                    isEq = true
                    break
                }
            }
            if (inserted) {
                continue
            }
            if (!inserted && !isEq) {
                increaseVector.addElement(cur)
                continue
            }
            inserted = false
            for (j in 0 until decreaseVector.size) {
                if (cur > decreaseVector[j]) {
                    decreaseVector.insertElementAt(cur, j)
                    inserted = true
                    break
                } else if (cur == decreaseVector[j]) {
                    println("NO")
                    return
                }
            }
            if (!inserted) {
                decreaseVector.addElement(cur)
            }
        }
        println("YES")
        println(increaseVector.size)
        for (iv in increaseVector) {
            print("$iv ")
        }
        println()
        println(decreaseVector.size)
        for (dv in decreaseVector) {
            print("$dv ")
        }
        println()
    }

    val input = Scanner(System.`in`)

    solve(input)
}
