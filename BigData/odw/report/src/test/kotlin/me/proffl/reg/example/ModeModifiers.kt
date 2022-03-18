package me.proffl.reg.example

import me.proffl.util.RegUtils

fun main() {
    fun printResult(regStr: String, str: String) {
        val result = RegUtils.match(regStr, str)

        if (result != null) {
            println("$regStr matching $str result: ${result.groups}")
        } else {
            println("$regStr doesn't matching $str ")
        }
    }

    /**
     * (?i) Ignore case mode
     * (?s) match all characters, including line breaks
     * (?m) Multiline mode
     * (?u) unicode aware case folding
     * (?U) Unicode matching
     * (?x) Comment mode: Allows for the presence of whitespace and comments in the regex pattern
     * (?d) Unix line mode
     */

    val str = """Java regex
        Embedded Mode""".trimMargin()
    println("regex expression will not match multilines in default:")
    printResult("\\AJava.*Mode\\z", str)

    println("change to match all characters mode:")
    printResult("(?s)\\AJava.*Mode\\z", str)

    // reg with comment and multi modes
    val reg = """(?ixs)\\A # asset start of the string
        Java
        \\s
        regex
        .*
        Mode
        \\z # asset end of the string
    """.trimIndent()
    printResult(reg, str)
}