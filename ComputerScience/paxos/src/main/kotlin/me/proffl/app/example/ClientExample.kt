package me.proffl.app.example

import me.proffl.client.SocketClient
import me.proffl.server.ServerSocket
import me.proffl.worker.EchoReader
import me.proffl.worker.SystemInWriter
import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.SocketChannel



fun main(args: Array<String>) {
//    val client = SocketClient("localhost", 8890, EchoReader(), SystemInWriter())
//    client.connect()
//    Thread(client).start()
    for (i in 0 .. 10) {
        val client = SocketChannel.open(InetSocketAddress("127.0.0.1", 8890))
        Thread {
            run {
                while (true) {
                    val bytebuffer = ByteBuffer.allocate(1024)
                    val bufSize = client.read(bytebuffer)
                    println(String(bytebuffer.array()).substring(0, bufSize))
                }
            }
        }.start()
    }
}
