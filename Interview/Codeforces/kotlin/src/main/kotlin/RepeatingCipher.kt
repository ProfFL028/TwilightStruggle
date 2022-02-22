import java.util.*


fun main(args: Array<String>) {

    fun solve(input: Scanner) {
        val length = input.nextInt()
        var encoder = input.next()!!
        encoder = encoder.substring(0, length)
        val sb = StringBuilder()
        var i = 0
        var j = 1
        while (i < encoder.length) {
            sb.append(encoder[i])
            i += j
            j += 1
        }
        println(sb.toString())
    }

    val input = Scanner(System.`in`)

    solve(input)
}
