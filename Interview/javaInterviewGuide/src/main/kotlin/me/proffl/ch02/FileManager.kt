package me.proffl.ch02

import java.io.File
import java.util.Stack

data class FileWithDepth(var file: File, var depth: Int) {
    override fun toString(): String {
        val sb = StringBuilder()
        for (i in 0 until depth)
            sb.append("\t")
        sb.append(file.name)
        if (file.isDirectory)
            sb.append("/")
        return sb.toString()
    }

}

fun main() {
    val file = File("src/main/kotlin/")
    if (!file.exists()) {
        file.mkdirs()
    }
    val files = file.listFiles()
    val stack = Stack<FileWithDepth>()
    if (files != null) {
        stack.add(FileWithDepth(file, 0))
        while (stack.isNotEmpty()) {
            val fd = stack.pop()
            if (fd.file.isDirectory) {
                val innerDir = fd.file.listFiles()
                if (innerDir != null) {
                    for (i in innerDir.indices.reversed()) {
                        stack.add(FileWithDepth(innerDir[i], fd.depth+1))
                    }
                }
            }
            println(fd)
        }
    }
}