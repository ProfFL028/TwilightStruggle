import java.util.*


fun main(args: Array<String>) {
    fun solve(input: Scanner) {
        val numStudent = input.nextInt()
        val skillCounts = Vector<Int>(numStudent)
        for (i in 0 until numStudent) {
            val skillCount = input.nextInt()
            var inserted = false
            for (j in 0 until i) {
                if (skillCount <= skillCounts[j]) {
                    skillCounts.insertElementAt(skillCount, j)
                    inserted = true
                    break
                }
            }
            if (!inserted) {
                skillCounts.addElement(skillCount)
            }
        }
        var learnCount = 0
        for (i in 0 until numStudent step 2) {
            learnCount += skillCounts[i+1] - skillCounts[i]
        }
        println(learnCount)
    }

    val input = Scanner(System.`in`)

    solve(input)
}
