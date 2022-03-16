package me.proffl.reg

import java.util.regex.Pattern

fun main() {
    val expr1 = "data[xxx][yyy]"
    val expr2 = "data [ aaa ]"
    val expr3 = "data "
    val pattern = Pattern.compile("(\\w+)(/[[\\w+]/]){0,2}")

    val matcher = pattern.matcher(expr1)
    if (matcher.matches()) {
        println("$expr1 is matches pattern")
        for (i in 0 until matcher.groupCount()) {
            println("group $i: ${matcher.group(i)}")
        }
    } else {
        println("$expr1 doesn't matches pattern")
    }
}