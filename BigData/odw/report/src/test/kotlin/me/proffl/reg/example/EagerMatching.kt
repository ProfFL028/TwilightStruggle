package me.proffl.reg.example

/**
 * Regular Expression is in `Eager Mode` by default, which means when the expression fails to match the string, it will stop matching quickly and rollback to the latest matching position.
 */
fun main() {
    val str = "whiteHouse"
    val regLessFirst = "(white|whiteHouse)"
    val regMoreFirst = "(whiteHouse|white)"

    var eagerRegex = Regex(regLessFirst)
    println("eagerRegex:")
    var result = eagerRegex.find(str)!!.groups[0]!!
    println("$regLessFirst matching $str -> ${result.value}")

    eagerRegex = Regex(regMoreFirst)
    result = eagerRegex.find(str)!!.groups[0]!!
    println("$regMoreFirst matching $str -> ${result.value}")

    var lazyRegex = Regex("$regLessFirst?")
    println("lazyRegex:")
    result = lazyRegex.find(str)!!.groups[0]!!
    println("$regLessFirst? matching $str -> ${result.value}")
    lazyRegex = Regex("$regMoreFirst?")
    result = lazyRegex.find(str)!!.groups[0]!!
    println("$regMoreFirst? matching $str -> ${result.value}")

    var possessiveRegex = Regex("$regLessFirst+")
    println("possessiveRegex:")
    result = possessiveRegex.find(str)!!.groups[0]!!
    println("$regLessFirst+ matching $str -> ${result.value}")
    possessiveRegex = Regex("$regMoreFirst+")
    result = possessiveRegex.find(str)!!.groups[0]!!
    println("$regMoreFirst+ matching $str -> ${result.value}")
}
