package me.proffl.worker

import java.nio.ByteBuffer
import java.nio.channels.SocketChannel

abstract class ChannelWriter {

    fun write(socketChannel: SocketChannel) {
        val byteBuffer = ByteBuffer.allocate(1024)

        socketChannel.write(pendingData())
    }

    abstract fun pendingData(): ByteBuffer
}
