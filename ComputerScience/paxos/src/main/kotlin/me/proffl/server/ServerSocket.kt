package me.proffl.server

import me.proffl.channel.factory.ChannelFactory
import me.proffl.worker.ChannelReader
import me.proffl.worker.ChannelWriter
import org.slf4j.LoggerFactory
import java.net.Socket
import java.nio.channels.SelectionKey
import java.nio.channels.ServerSocketChannel
import java.nio.channels.SocketChannel

class ServerSocket(
    var port: Int,
    var readWorker: ChannelReader,
    var writeWorker: ChannelWriter
) :
    Runnable {
    companion object {
        private val logger = LoggerFactory.getLogger(ServerSocket::class.java)
    }
    private val selector = ChannelFactory.openSelector()

    fun open() {
        ChannelFactory.registerServerSocketChannel(selector, port)
    }

    override fun run() {
        while (true) {
            this.selector.select()
            val selectedKeys = this.selector.selectedKeys().iterator()
            while (selectedKeys.hasNext()) {
                val key = selectedKeys.next()
                selectedKeys.remove()

                try {
                    if (key.isAcceptable) {
                        this.accept(key)
                    } else if (key.isReadable) {
                        this.read(key)
                    } else if (key.isWritable) {
                        this.write(key)
                    }
                } catch (e: Exception) {
                    logger.error(e.message)
                    key.cancel()
                    key.channel().close()
                }
            }
        }
    }

    private fun accept(key: SelectionKey) {
        val serverSocketChannel = key.channel() as ServerSocketChannel
        val socketChannel = serverSocketChannel.accept()
        socketChannel.configureBlocking(false)
        val socket = socketChannel.socket()
        socketChannel.register(this.selector, SelectionKey.OP_WRITE)

        logger.info("a client is connected to server: ${socket.inetAddress}:${socket.port}")
    }

    private fun read(key: SelectionKey) {
        this.readWorker.read(key)
    }

    private fun write(key: SelectionKey) {
        this.writeWorker.write(key)
    }

}
