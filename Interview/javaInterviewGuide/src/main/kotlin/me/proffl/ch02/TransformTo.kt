package me.proffl.ch02

import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream

fun main() {
    val input = FileInputStream("test.txt")
    val output  = File("out.txt")
    if (!output.exists()) {
        output.createNewFile()
    }
    input.transferTo(FileOutputStream(output))
    input.close()
}