import java.util.*

fun charToInt(c: Char): Int {
    return c - 'a'
}

fun intToChar(i: Int): Char {
    return 'a' + i
}

fun main() {
    fun solve(input: Scanner) {
        val strLen = input.nextInt()
        val str1 = input.next()
        val str2 = input.next()

        val result = Array(strLen) { ' ' }
        var extra = 0
        for (i in 0 until strLen) {
            var sum = charToInt(str1[i]) + charToInt(str2[i]) + extra
            if (sum >= 52) {
                sum -= 52
                for (j in i - 1 downTo 0) {
                    if (result[j] == 'z') {
                        result[j] = 'a'
                    } else {
                        result[j] = result[j] + 1
                        break
                    }
                }
            }
            result[i] = intToChar(sum / 2)
            if (sum % 2 == 1) {
                extra = 26
            } else {
                extra = 0
            }
        }
        for (c in result) {
            print(c)
        }
        println()
    }

    val input = Scanner(System.`in`)
    solve(input)

}