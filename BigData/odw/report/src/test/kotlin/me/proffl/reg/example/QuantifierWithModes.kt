package me.proffl.reg.example

import me.proffl.util.RegUtils

/**
 * GreedyQuantifier: default
 * LazyQuantifier: ?
 * PossessiveQuantifier: +
 *
 * normally possessive model will speed up performance for not rolling back idx, but may cause some problem.
 */
fun main() {
    fun printResult(regStr: String, str: String) {
        val result = RegUtils.match(regStr, str)

        if (result != null) {
            println("$regStr matching $str result: ${result.groups[0]}")
        } else {
            println("$regStr doesn't matching $str ")
        }
    }

    val a1b5 = "a1b5"
    printResult("\\w+\\d", a1b5)
    printResult("\\w+?\\d", a1b5)
    printResult("\\w++\\d", a1b5)

    println()

    val s1 = "as-df9999"
    val s2 = "asdf-:123"
    val eagerReg = "^[a-zA-Z-]+[^:].*$"
    printResult(eagerReg, s1)
    printResult(eagerReg, s2)
    val possReg = "^[a-zA-Z-]++[^:].*$"
    printResult(possReg, s1)
    printResult(possReg, s2)
}