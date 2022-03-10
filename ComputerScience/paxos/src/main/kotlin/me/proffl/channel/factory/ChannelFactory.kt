package me.proffl.channel.factory

import org.slf4j.LoggerFactory
import java.net.InetSocketAddress
import java.nio.channels.SelectionKey
import java.nio.channels.Selector
import java.nio.channels.SocketChannel

/**
 * Factory class for creating Selector, ServerSocketChannel and SocketChannel.
 */
class ChannelFactory {

    companion object {
        private val logger = LoggerFactory.getLogger(ChannelFactory::class.java)

        /**
         * Open a nio Selector class. Selector use one thread instead of several to manage multi channels.
         */
        fun openSelector(retry: Int = -1, retrySleep: Long = 60 * 1000): Selector {
            var tried = 0
            while (true) {
                try {
                    return Selector.open()
                } catch (e: Exception) {
                    logger.error(e.message)
                }
                if (retry > 0 && tried < retry) {
                    try {
                        Thread.sleep(retrySleep)
                    } catch (e: Exception) {
                        logger.error(e.message)
                    }
                    tried++
                    logger.warn("Open Selector tried $tried times");
                }

            }
        }

        fun registerSocketChannel(selector: Selector, host: String, port: Int):SelectionKey {
            selector.select()
            val socketAddress = InetSocketAddress(host, port)
            val socketChannel = SocketChannel.open(socketAddress)
            socketChannel.configureBlocking(false)
            val selectionKey = socketChannel.register(selector, SelectionKey.OP_CONNECT)
            selector.wakeup()
            return selectionKey
        }
    }
}