package me.proffl.ch02

import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.AsynchronousSocketChannel

class AIOClient {
    private val asc = AsynchronousSocketChannel.open()

    fun connect(ip:String, port:Int) {
        asc.connect(InetSocketAddress(ip, port)).get()
    }

    fun write(data: String) {
        asc.write(ByteBuffer.wrap(data.toByteArray())).get()
        read()
    }

    private fun read() {
        val buffer = ByteBuffer.allocate(1024)
        asc.read(buffer).get()
        buffer.flip()

        val responseBytes = ByteArray(buffer.remaining())
        buffer.get(responseBytes)
        println(String(responseBytes).trim())
        asc.close()
    }
}

fun main() {
    val ip = "127.0.0.1"
    val port = 8765

    val client = AIOClient()
    client.connect(ip, port)
    client.write("hello world!")
}