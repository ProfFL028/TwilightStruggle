package me.proffl.reg.example.group

import me.proffl.util.RegUtils

fun main() {
    val reg = "(?<id>\\d+):(?<subject>[a-zA-Z]+):(?<score>\\d+):(?<term>[A-Z]+)"
    val str = "123456:Science:97:II"
    RegUtils.matchAndPrint(reg, str)
}