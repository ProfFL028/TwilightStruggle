package me.proffl.worker

import java.nio.ByteBuffer
import java.nio.channels.SocketChannel

abstract class ChannelWriter {
    protected lateinit var pendingData: ByteBuffer
    fun write(socketChannel: SocketChannel) {
        socketChannel.write(pendingData)
    }


}