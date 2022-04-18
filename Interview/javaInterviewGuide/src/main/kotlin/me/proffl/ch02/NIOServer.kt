package me.proffl.ch02

import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.SelectionKey
import java.nio.channels.Selector
import java.nio.channels.ServerSocketChannel
import java.nio.channels.SocketChannel


class NIOServer(var port: Int = 8765) : Runnable {
    private val selector = Selector.open()
    private val readBuffer = ByteBuffer.allocate(1024)
    private val writeBuffer = ByteBuffer.allocate(1024)

    init {
        val ssc = ServerSocketChannel.open()
        ssc.configureBlocking(false) // important
        ssc.bind(InetSocketAddress(port))
        ssc.register(selector, SelectionKey.OP_ACCEPT)
        println("Server started")
    }

    override fun run() {
        while (true) {
            this.selector.select();
            val keys = this.selector.selectedKeys().iterator();
            // 进行遍历
            while (keys.hasNext()) {
                val key = keys.next()
                keys.remove();
                if (key.isValid) {
                    if (key.isAcceptable) {
                        accept(key); }
                    if (key.isReadable) {
                        read(key); }
                    if (key.isWritable) {
                        write(key); }
                }
            }
        }
    }

    private fun accept(key: SelectionKey) {
        val ssc = key.channel() as ServerSocketChannel
        val sc = ssc.accept()
        sc.configureBlocking(false)
        sc.register(this.selector, SelectionKey.OP_READ or SelectionKey.OP_WRITE)
    }

    private fun read(key: SelectionKey) {
        val sc = key.channel() as SocketChannel
        val count: Int = sc.read(this.readBuffer)

        if (count == -1) {
            key.channel().close()
            key.cancel()
            return
        }
        readBuffer.flip()

        val bytes = ByteArray(this.readBuffer.remaining())
        readBuffer.get(bytes)

        readBuffer.clear()
        val body = String(bytes).trim { it <= ' ' }
        println("Server get response: $body")
        sc.register(this.selector, SelectionKey.OP_WRITE)
    }

    private fun write(key: SelectionKey) {
        val sc = key.channel() as SocketChannel

        writeBuffer.put("Response from server: ".toByteArray())

        writeBuffer.flip()
        sc.write(writeBuffer)
        writeBuffer.clear()
        key.interestOps(SelectionKey.OP_READ)
    }
}

fun main() {
    val server = Thread(NIOServer())
    server.start()
}