package me.proffl.util

class RegUtils {
    companion object {
        fun match(regStr: String, expr: String): MatchResult? {
            val reg = Regex(regStr)
            return reg.find(expr)
        }

        fun matchAndPrint(reg: String, str: String) {
            val result = match(reg, str)

            if (result != null) {
                println(reg)
                println("matching:")
                println(str)
                println("result groups:")
                for (i in 1 until result.groups.size) {
                    println("group result $i:")
                    println(result.groups[i]!!.value)
                }
            } else {
                println("$reg doesn't matching $str ")
            }
        }
    }
}