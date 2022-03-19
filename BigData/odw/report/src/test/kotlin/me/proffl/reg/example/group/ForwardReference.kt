package me.proffl.reg.example.group

import me.proffl.util.RegUtils

fun main() {
    RegUtils.matchAndPrint("^(\\d+)-(?:\\2[0-9A-Fa-f]{4}|(\\d*.?\\d+:))+$", "666-6.6:6.6:abcd3.3:")
    RegUtils.matchAndPrint("^(\\d+)-(?:\\2[0-9dA-Fa-f]{4}|(\\d*.?\\d+:))+$", "666-3.3:5.5:5.5:abcd")

    val reg = "^(?:\\1#color(red|blue|white)+)$"
    RegUtils.matchAndPrint(reg, "blue")
    RegUtils.matchAndPrint(reg, "redblue")
    RegUtils.matchAndPrint(reg, "blueblueblue")
    RegUtils.matchAndPrint(reg, "redbluewhite")
    RegUtils.matchAndPrint(reg, "redred#color")
    RegUtils.matchAndPrint(reg, "whitewhite#color")
    RegUtils.matchAndPrint(reg, "blueredred#color")


    RegUtils.matchAndPrint(reg, "#color")
    RegUtils.matchAndPrint(reg, "red#color")
    RegUtils.matchAndPrint(reg, "bluered#color")
    RegUtils.matchAndPrint(reg, "redbluefruit")
    RegUtils.matchAndPrint(reg, "redbluered#color")
}