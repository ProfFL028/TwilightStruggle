package me.proffl.reg.example

import me.proffl.util.ArrayUtils


val x = byteArrayOf(0, 1, 2, 3, 4, 5, 6, 7, 8, 0x00A, 0x0009, 0x000D, 0x000C, 0x001B, 0x0007)
val xStr = ArrayUtils.format(x)

fun main() {
    fun printResult(reg: Regex) {
        val str = x.decodeToString()

        val result = reg.find(str)
        if (result != null) {
            println("${reg.pattern} matching $xStr result: ${result.groups[0]}")
        } else {
            println("${reg.pattern} doesn't matching $xStr ")
        }
    }

    // a character with the octal value c \0c
    printResult(Regex("\\07"))

    // a character with the octal value cc \0cc
    printResult(Regex("\\007"))

    // a character with the octal value ncc \0ncc where n cannot be more than 3
    printResult(Regex("\\0007"))

    // a character with the hex value hh \xhh
    printResult(Regex("\\x05"))

    // a character with the hex value hhhh \uhhhh
    printResult(Regex("\\u0005"))

    // a character with the hex value hhhh \x{h....h} where 0xh..h must be a valid CODE_POINT
    printResult(Regex("\\x{00005}"))

    // \n -> u000A
    printResult(Regex("\\n"))

    // \t -> u0009
    printResult(Regex("\\t"))

    // \r -> u000D
    printResult(Regex("\\r"))

    // \f -> u000C
    printResult(Regex("\\f"))

    // \e -> u001B
    printResult(Regex("\\e"))

    // \a -> u0007
    printResult(Regex("\\a"))

    // \cn control character represented by n
    printResult(Regex("\\c1"))
}
