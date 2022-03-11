package me.proffl.worker

import java.nio.ByteBuffer
import java.nio.channels.SocketChannel

abstract class ChannelReader {

    fun read(channel: SocketChannel) {
        val byteBuffer = ByteBuffer.allocate(1024 * 1024 * 1)
        var bufferSize = -1
        do {
            bufferSize = channel.read(byteBuffer)
            if (bufferSize == -1) {
                throw RuntimeException("Read Error from channel!")
            }
            handle(byteBuffer, bufferSize)
        } while (bufferSize > 0)
    }

    abstract fun handle(byteBuffer: ByteBuffer, bufferSize:Int)
}