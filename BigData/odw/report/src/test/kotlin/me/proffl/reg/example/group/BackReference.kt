package me.proffl.reg.example.group

import me.proffl.util.RegUtils

fun main() {
    RegUtils.matchAndPrint("^(\\d)\\1$", "55")
    RegUtils.matchAndPrint("^(\\d)\\1{4}$", "55555")

    RegUtils.matchAndPrint("^(\\d{2})[:/-](\\d{2})[:/-]\\1[:/-]\\2$", "12-45:12/45")
    RegUtils.matchAndPrint("^(\\d{2})[:/-](\\d{2})[:/-]\\1[:/-]\\2$", "12-45:12/46")

    RegUtils.matchAndPrint("^(['\"])\\w+\\1$", "'ab'")
    RegUtils.matchAndPrint("^(['\"])\\w+\\1$", "'ab\"")

    // back reference of a named group
    RegUtils.matchAndPrint("^(?<matchedDigits>\\d+)\\s+\\k<matchedDigits>$", "1234 1234")
}