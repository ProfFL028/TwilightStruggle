package me.proffl.ch02

import java.io.RandomAccessFile
import java.nio.ByteBuffer

fun main() {
    val fromFile = RandomAccessFile("test.txt", "rw")
    // open a channel
    val fromChannel = fromFile.channel

    val toFile = RandomAccessFile("out.txt", "rw")
    val toChannel = toFile.channel

    // transform to another channel
    fromChannel.transferTo(0, fromChannel.size(), toChannel)

    // read from channel
    val buffer = ByteBuffer.allocate(48)
    var bytesRead = fromChannel.read(buffer)
    println(buffer.toString())

    // write to channel
    val newInfo = "\nNew String to the file"
    val writeBuffer = ByteBuffer.allocate(48)
    writeBuffer.clear()
    writeBuffer.put(newInfo.toByteArray())
    writeBuffer.flip() // switch from write and read.
    while (writeBuffer.hasRemaining()) {
        fromChannel.write(writeBuffer)
    }

    fromChannel.close()
    toChannel.close()
}