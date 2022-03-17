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

    // we need to wrap `\` before special characters.
    val str = "a.b?"
    val reg = "a\\.b\\?"
    printResult(reg, str)

    val str2 = "{food}"
    val reg2 = "\\{food\\}"
    printResult(reg2, str2)

    // and we don't need to add `\` inside character class, except ^, -, ] and \
    val  reg3 = "^[@*+$#?.]+$"
    val str3 = "@#%$.*"
    printResult(reg3, str3)

    val reg4 = "^[a-zA-Z$"
}