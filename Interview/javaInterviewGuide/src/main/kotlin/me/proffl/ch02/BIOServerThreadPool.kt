package me.proffl.ch02

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.net.ServerSocket
import java.net.Socket
import java.util.concurrent.ArrayBlockingQueue
import java.util.concurrent.ThreadPoolExecutor
import java.util.concurrent.TimeUnit

class BIOServerHandler(var id: Int, var socket: Socket) : Runnable {
    override fun run() {
        val reader = BufferedReader(InputStreamReader(socket.getInputStream()))
        val writer = PrintWriter(socket.getOutputStream(), true)

        var body: String? = null
        while (true) {
            body = reader.readLine()
            println("Server Message: $body")
            writer.println("Response from server $id")
        }
    }
}

class BIOServerPool(var maxPoolSize: Int, var queueSize: Int) {
    private val executor: ThreadPoolExecutor = ThreadPoolExecutor(
        Runtime.getRuntime().availableProcessors(),
        maxPoolSize, 120L, TimeUnit.SECONDS, ArrayBlockingQueue(queueSize)
    )

    fun execute(task: Runnable) {
        this.executor.execute(task)
    }
}

fun main() {
    val server = ServerSocket(8765)
    val pool = BIOServerPool(50, 1000)
    var id = 1
    while (id < 2000) {
        val socket = server.accept()
        pool.execute(BIOServerHandler(id, socket))
        id++
    }

    server.close()
}