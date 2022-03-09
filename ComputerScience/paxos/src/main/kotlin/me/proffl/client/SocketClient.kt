package me.proffl.client

import me.proffl.channel.factory.ChannelFactory
import java.nio.channels.SelectionKey
import java.nio.channels.Selector

class SocketClient(var host: String, var port: Int): Runnable {
    private val selector: Selector = ChannelFactory.openSelector()
    private lateinit var key: SelectionKey

    fun connect() {
        key = ChannelFactory.registerSocketChannel(selector, host, port)
    }

    override fun run() {
        while (true) {
            selector.keys()
        }
    }

}
