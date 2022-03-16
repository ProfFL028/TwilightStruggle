package me.proffl.reg.example

import me.proffl.util.RegUtils

/**
 * supported quantifiers:
 * * zero or more times
 * + at least one times
 * ? one or zero times
 * {X} exactly X times
 * {X,} X or more times
 * {X, Y} at least X and at most Y times
 */
fun main() {
    fun printMatch(regStr: String) {
        val digits = arrayListOf(".45", "1234567", "5", "123.45", "+67.55", "-9832.23")

        for (digit in digits) {
            val result = RegUtils.match(regStr, digit)

            if (result != null) {
                println("$regStr matching $digit result: ${result.groups[0]}")
            } else {
                println("$regStr doesn't matching $digit ")
            }
        }
    }

    printMatch("\\d{1,3}")
    println()
    println()
    printMatch("^[+-]?\\d*\\.?\\d+$")

}