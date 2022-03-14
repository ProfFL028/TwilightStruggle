package me.proffl.client

import me.proffl.channel.factory.ChannelFactory
import me.proffl.worker.ChannelReader
import me.proffl.worker.ChannelWriter
import org.slf4j.LoggerFactory
import java.nio.channels.SelectionKey
import java.nio.channels.Selector
import java.nio.channels.SocketChannel
import java.util.logging.Logger

class SocketClient(
    var host: String,
    var port: Int,
    var readWorker: ChannelReader,
    var writeWorker: ChannelWriter
) : Runnable {

    companion object {
        private val logger = LoggerFactory.getLogger(SocketClient::class.java)
    }
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

                try {
                    if (key.isConnectable) {
                        this.finishConnection(key)
                    } else if (key.isReadable) {
                        this.read(key)
                    } else if (key.isWritable) {
                        this.write(key)
                    }
                } catch (e: Exception) {
                    logger.info(e.message)
                    key.cancel()
                    key.channel().close()
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
    }

    private fun read(key: SelectionKey) {
        this.readWorker.read(key)
    }

    private fun write(key: SelectionKey) {
        this.writeWorker.write(key)
    }
}
