package me.proffl.reg.example.group

import me.proffl.util.RegUtils.Companion.matchAndPrint

fun main() {
    val reg1 = "^((\\d+)-([a-zA-Z]+))$"
    val str1 = "1234-aBc"
    matchAndPrint(reg1, str1)

    // group numbering start from 1, and group 0 always refer to entire matched text
    val reg2 = "(((a|b)-(c|d))/(\\d+))"
    matchAndPrint(reg2, "a-c/15")
    matchAndPrint(reg2, "a-d/99")
    matchAndPrint(reg2, "b-c/567")
    matchAndPrint(reg2, "b-d/1000")

    // repeated matches in a capturing group using a quantifier, it will capture the last matched text in the given group
    // it only captures last match `word`!!
    matchAndPrint("(\\w+\\s+){3}", "around the word ")
}