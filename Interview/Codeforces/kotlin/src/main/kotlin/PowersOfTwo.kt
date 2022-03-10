import java.util.*
import java.util.concurrent.ThreadLocalRandom
import kotlin.collections.ArrayList

fun main() {
    fun subPrint(bitIndex: Int, remains: Long) {
        if (remains == 0L) {
            return
        }
        if (remains == 1L) {
            print("${1 shl bitIndex} ")
            return
        }
        subPrint(bitIndex - 1, remains / 2L)
        subPrint(bitIndex - 1, remains - (remains / 2L))
    }

    fun solve(input: Scanner) {
        val n = input.nextLong()
        val k = input.nextLong()
        // val n = 426101272L // ThreadLocalRandom.current().nextLong(5, 1000000000L)
        // val k = 584L // ThreadLocalRandom.current().nextLong(5, 1000L)
        if (k > n) {
            println("NO")
            return
        }
        if (k == n) {
            println("YES")
            var i = 0
            while (i < k) {
                print("1 ")
                i++
            }
            println()
            return
        }

        val bitset = ArrayList<Int>()
        var i = 0
        var progress = n
        while (progress  > 0L) {
            if (progress % 2L == 1L) {
                bitset.add(i)
            }
            progress /= 2L
            i++
        }

        if (bitset.size > k) {
            println("NO")
            return
        }
        println("YES")
        var remains = k - bitset.size
        for (i in bitset) {
            if (i == 0) {
                print("1 ")
            } else {
                val canHandle = 1 shl i
                if (remains == 0L) {
                    print("${1 shl i} ")
                } else {
                    if (remains >= canHandle) {
                        for (j in 0 until canHandle) {
                            print("1 ")
                        }
                        remains -= canHandle - 1
                    } else {
                        subPrint(i, remains + 1)
                        remains = 0
                    }
                }
            }
        }
        println()
    }

    val input = Scanner(System.`in`)

        solve(input)
}
