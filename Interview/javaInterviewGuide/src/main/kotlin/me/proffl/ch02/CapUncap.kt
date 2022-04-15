package me.proffl.ch02

import java.io.BufferedInputStream
import java.io.FileInputStream
import java.io.FilterInputStream
import java.io.InputStream

class CapUncapIO(var input: InputStream): FilterInputStream(input) {

    override fun read(): Int {
        var c = 0
        c = super.read()
        if (c != -1) {
            if (c.toChar().isLowerCase()) {
                c = c.toChar().uppercaseChar().code
            } else if (c.toChar().isUpperCase()) {
                c = c.toChar().lowercaseChar().code
            }
        }
        return c
    }
}

fun main() {
    val input = CapUncapIO(BufferedInputStream(FileInputStream("test.txt")));
    var c = input.read()
    while (c>=0) {
        print(c.toChar())
        c = input.read()
    }
    input.close()
}