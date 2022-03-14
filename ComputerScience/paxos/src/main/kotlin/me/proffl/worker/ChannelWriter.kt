package me.proffl.worker

import java.nio.ByteBuffer
import java.nio.channels.SelectionKey
import java.nio.channels.SocketChannel
import java.util.concurrent.ConcurrentLinkedDeque

abstract class ChannelWriter {

    fun write(key: SelectionKey) {
        val channel = key.channel() as SocketChannel
        while (!pendingData.isEmpty()) {
            val str = pendingData.pop()
            val buffer = ByteBuffer.allocate(str.length)
            buffer.put(str.toByteArray())
            buffer.flip() !!!!
            channel.write(buffer)
            while (buffer.hasRemaining()) {
                channel.write(buffer)
            }
            buffer.clear()
        }
//        key.interestOps(SelectionKey.OP_READ)
    }

    protected val pendingData = ConcurrentLinkedDeque<String>()
}
