package me.proffl.worker

import java.io.BufferedWriter
import java.util.Scanner

class SystemInWriter : ChannelWriter(), Runnable {
    override fun run() {
        while (true) {
            val scanner = Scanner(System.`in`)
            pendingData.add(scanner.nextLine())
        }
    }
}
