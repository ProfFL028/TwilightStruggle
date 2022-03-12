package me.proffl.server

import me.proffl.channel.factory.ChannelFactory
import me.proffl.worker.ChannelReader
import me.proffl.worker.ChannelWriter
import java.net.Socket
import java.nio.channels.SelectionKey
import java.nio.channels.ServerSocketChannel
import java.nio.channels.SocketChannel

class ServerSocket(
    var host: String,
    var port: Int,
    var readWorker: ChannelReader,
    var writeWorker: ChannelWriter
) :
    Runnable {
    private val selector = ChannelFactory.openSelector()

    fun open() {
        ChannelFactory.registerServerSocketChannel(selector, host, port)
    }

    override fun run() {
        while (true) {
            this.selector.select()
            val selectedKeys = this.selector.selectedKeys().iterator()
            while (selectedKeys.hasNext()) {
                val key = selectedKeys.next()
                selectedKeys.remove()
                if (!key.isValid) {
                    continue
                }

                if (key.isAcceptable) {
                    this.accept(key)
                } else if (key.isReadable) {
                    this.read(key)
                } else if (key.isWritable) {
                    this.write(key)
                }
            }
        }
    }

    private fun accept(key: SelectionKey) {
        val serverSocketChannel = key.channel() as ServerSocketChannel
        val socketChannel = serverSocketChannel.accept()
        // socketChannel.socket()
        socketChannel.configureBlocking(false)

        socketChannel.register(this.selector, SelectionKey.OP_READ)
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
