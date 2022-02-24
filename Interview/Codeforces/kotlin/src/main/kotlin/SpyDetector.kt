import java.util.*



fun main(args: Array<String>) {

    val input = Scanner(System.`in`)
    var testCases = input.nextInt()


    fun solve(input: Scanner) {
        val arrSize = input.nextInt()

        val preValue = input.nextInt()
        val curValue = input.nextInt()
        var constant: Int? = null
        if (preValue == curValue) {
            constant = preValue
        }
        var idx = 0
        for (i in 2 until arrSize) {
            val now = input.nextInt()
            if (constant != null) {
                if (now != constant) {
                    idx = i+1
                }
            } else {
                if (now == preValue) {
                    idx = 2
                } else {
                    idx = 1
                }
            }
        }
        println(idx)
    }


    while (testCases > 0) {
        solve(input)
        testCases--
    }
}
