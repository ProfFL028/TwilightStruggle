package me.proffl.configserver

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication

@SpringBootApplication
class CsApplication

fun main(args: Array<String>) {
    runApplication<CsApplication>(*args)
}
