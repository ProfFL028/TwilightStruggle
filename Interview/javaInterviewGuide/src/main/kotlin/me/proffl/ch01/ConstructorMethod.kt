package me.proffl.ch01

class ConstructorMethod {
    fun ConstructorMethod() {
        println("It is allowed but not recommended")
    }
}

fun main() {
    val cm = ConstructorMethod()
    cm.ConstructorMethod()
}