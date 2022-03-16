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
    // \b position between a word and a non-word character
    val str1 = "Hat at work"
    printResult("\\bat\\b", str1)
    // \B position non-word boundaary
    printResult("\\Bat\\b", str1)
    // ^ every beginning $ every end
    // \A permanent start of input. in a multiline input.
    // \z permanent end of input. in a multiline input.
    // \Z similar to \z except that it mathces just before the optional line break at the very end of the input.
    val str2 = "suppress expression press depression"
    printResult("\\Bpress\\B", str2)

    val str3 = "ppp\n555\n"
    printResult("\\Ap+\\n5{3}\\Z", str3)
    printResult("\\Ap+\\n5{3}\\z", str3)
    printResult("\\Ap+\\n5{3}\\n\\z", str3)
}