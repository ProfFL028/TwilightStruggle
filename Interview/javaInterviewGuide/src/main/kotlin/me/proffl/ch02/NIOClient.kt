package me.proffl.ch02

import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.SocketChannel

fun main() {
    val socketChannel = SocketChannel.open()
    socketChannel.connect(InetSocketAddress("127.0.0.1", 8765))
    val writeBuffer = ByteBuffer.allocate(1024)
    val readBuffer = ByteBuffer.allocate(1024)

    while (true) {
        val byteArray = ByteArray(1024)
        System.`in`.read(byteArray)
        writeBuffer.put(byteArray)

        writeBuffer.flip()
        socketChannel.write(writeBuffer)
        writeBuffer.clear()

        socketChannel.read(readBuffer)
        readBuffer.flip()

        val byteArray2 = ByteArray(1024)
        readBuffer.get(byteArray2)
        readBuffer.clear()
        val body = String(byteArray2)
        println("Client get message: $body")
    }
}