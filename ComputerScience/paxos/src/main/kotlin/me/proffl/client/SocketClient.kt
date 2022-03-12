package me.proffl.client

import me.proffl.channel.factory.ChannelFactory
import me.proffl.worker.ChannelReader
import me.proffl.worker.ChannelWriter
import java.nio.channels.SelectionKey
import java.nio.channels.Selector
import java.nio.channels.SocketChannel

class SocketClient(
    var host: String,
    var port: Int,
    var readWorker: ChannelReader,
    var writeWorker: ChannelWriter
) : Runnable {
    private val selector: Selector = ChannelFactory.openSelector()

    fun connect() {
        ChannelFactory.registerSocketChannel(selector, host, port)
    }

    override fun run() {
        while (true) {
            this.selector.select()
            val selectedKeys = this.selector.selectedKeys().iterator()
            while (selectedKeys.hasNext()) {
                val key = selectedKeys.next()
                selectedKeys.remove()
                if (!key.isValid) continue

                if (key.isConnectable) {
                    this.finishConnection(key)
                } else if (key.isReadable) {
                    this.read(key)
                } else if (key.isWritable) {
                    this.write(key)
                }
            }
        }
    }

    private fun finishConnection(key: SelectionKey) {
        val socketChannel = key.channel() as SocketChannel
        try {
            socketChannel.finishConnect()
        } catch (e: Exception) {
            key.cancel()
            return
        }

        key.interestOps(SelectionKey.OP_WRITE)
    }

    private fun read(key: SelectionKey) {
        val socketChannel = key.channel() as SocketChannel
        this.readWorker.read(socketChannel)
    }

    private fun write(key: SelectionKey) {
        val socketChannel = key.channel() as SocketChannel
        this.writeWorker.write(socketChannel)
    }
}
