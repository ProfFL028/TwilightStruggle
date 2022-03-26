package me.proffl.eurkaservice

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication

@SpringBootApplication
class EurkaServiceApplication

fun main(args: Array<String>) {
    runApplication<EurkaServiceApplication>(*args)
}
