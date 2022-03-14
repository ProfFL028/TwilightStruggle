package me.proffl.app.example

import me.proffl.server.ServerSocket
import me.proffl.worker.EchoReader
import me.proffl.worker.SystemInWriter


fun main(args: Array<String>) {
    val writer = SystemInWriter()
    Thread(writer).start()
    val serverSocket = ServerSocket(8890, EchoReader(), writer)
    serverSocket.open()
    Thread(serverSocket).start()
}
