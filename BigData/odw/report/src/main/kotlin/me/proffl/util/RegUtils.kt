package me.proffl.util

class RegUtils {
    companion object {
        fun match(regStr: String, expr: String): MatchResult? {
            val reg = Regex(regStr)
            return reg.find(expr)
        }
    }
}