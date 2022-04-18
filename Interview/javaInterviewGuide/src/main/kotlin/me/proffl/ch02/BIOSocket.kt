package me.proffl.ch02

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.net.ServerSocket
import java.net.Socket

class BIOClient: Runnable {
    override fun run() {
        val socket = Socket("127.0.0.1", 8765)
        val reader = BufferedReader(InputStreamReader(socket.getInputStream()))
        val out = PrintWriter(socket.getOutputStream(), true)
        out.println("Information comes from client")
        val response = reader.readLine()
        println("Client get information: $response")

        out.close()
        reader.close()
        socket.close()
    }
}

class BIOServer: Runnable {
    override fun run() {
        val socket = ServerSocket(8765).accept()
        val reader = BufferedReader(InputStreamReader(socket.getInputStream()))
        val out = PrintWriter(socket.getOutputStream(), true)

        while (true) {
            val body = reader.readLine()
            println("Server get message: $body")
        }
    }
}

fun main() {
    val server = Thread(BIOServer())
    server.start()
    val client = Thread(BIOClient())
    client.start()
}