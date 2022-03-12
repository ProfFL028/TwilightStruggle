package me.proffl.app.example

import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedDeque

class Producer : Runnable {
    val pendingData = ConcurrentLinkedDeque<String>()
    private val scanner = Scanner(System.`in`)
    override fun run() {
        while (true) {
            val value = scanner.next()
            synchronized(pendingData) { pendingData.add(value) }
        }
    }
}

class Consumer(var producer: Producer) : Runnable {
    override fun run() {
        while (true) {
            synchronized(producer.pendingData) {
                while (producer.pendingData.size > 0) {
                    val str = producer.pendingData.pop()
                    println(str)
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
