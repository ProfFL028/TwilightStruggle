package me.proffl.reg.example.group

import me.proffl.util.RegUtils

fun main() {
    val reg = "^(?:\\d{2})+$"
    val str = "22"
    println("it matches, but ignores matching group")
    RegUtils.matchAndPrint(reg, str)
    RegUtils.matchAndPrint("(?i:red|green|blue|white)", "White")

    RegUtils.matchAndPrint("(?:abc)", "abc")
    RegUtils.matchAndPrint("(?mi:abc)", "abc")
    RegUtils.matchAndPrint("((?:abc)?)", "abc")
}