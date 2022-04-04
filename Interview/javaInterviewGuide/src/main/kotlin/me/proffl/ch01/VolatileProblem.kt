package me.proffl.ch01

fun main() {
    var i = 0
    var f = false

    val r1 = Runnable {
        while (!f) {
            println(i)
        }
    }
    val r2 = Runnable {
        Thread.sleep(1000)
        i++
        f = true
    }
    Thread(r1).start()
    Thread(r2).start()
}