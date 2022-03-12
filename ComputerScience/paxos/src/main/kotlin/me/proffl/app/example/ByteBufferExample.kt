package me.proffl.app.example

import java.lang.Integer.min
import java.nio.ByteBuffer
import java.nio.charset.StandardCharsets


fun main() {
    val capacity = 10
    val byteBuffer = ByteBuffer.allocate(capacity)
    val str = """
        I'm a long long string with a lot of data who's length is greater than bytebuffer capacity!!
    """.trimIndent()

    val byteArray = str.toByteArray()

    println("byteArray Length is ${byteArray.size}")
    println(String(byteArray))

    var idx = 0
    val len = str.length
    while (idx < len) {
        val endIdx = min(len, idx + capacity)

        byteBuffer.put(str.substring(idx, endIdx).toByteArray())

        byteBuffer.flip() // !! import, set bytebuffer idx to zero.
        val byteArray = ByteArray(endIdx - idx)
        byteBuffer.get(byteArray)
        byteBuffer.clear() // !! import clear the bytebuffer after read the data.

        println(String(byteArray))
        idx += capacity
    }

}
