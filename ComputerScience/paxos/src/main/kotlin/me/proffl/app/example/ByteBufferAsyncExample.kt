package me.proffl.app.example

import java.nio.ByteBuffer
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedDeque

class Producer : Runnable {
    val pendingData = ConcurrentLinkedDeque<String>()
    private val scanner = Scanner(System.`in`)

    companion object {
        const val capability = 10
    }

    override fun run() {
        while (true) {
            val value = scanner.next()

            var idx = 0
            val len = value.length
            while (idx < len) {
                val endIdx = Integer.min(len, idx + capability)
                synchronized(pendingData) { pendingData.add(value.substring(idx, endIdx)) }
                idx += capability
            }
        }
    }
}

class Consumer(var producer: Producer) : Runnable {
    override fun run() {
        while (true) {
            synchronized(producer.pendingData) {
                while (producer.pendingData.size > 0) {
                    println(producer.pendingData.pop())
                }
            }
        }
    }

}


fun main() {
    val producer = Producer()
    val consumer = Consumer(producer)
    Thread(producer).start()
    Thread(consumer).start()
}
