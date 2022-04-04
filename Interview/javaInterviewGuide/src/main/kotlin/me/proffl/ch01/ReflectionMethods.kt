package me.proffl.ch01

class A {
    companion object {
        init {
            println("static init A")
        }
    }
    init {
        println("class init A")
    }
}

fun main() {
    // It will not call any static blocks.
    val a = A::class::java
    println("className: ${a.name}")
    println("className: ${a.javaClass.name}")
    val b = A::javaClass
    println("className: ${b.name}")
    println("className: ${b.javaClass.name}")
    val c = A::class.java  // it will return the same value as below.
    println("className: ${c.name}")


    // It will only call static blocks.
    // val a = Class.forName("me.proffl.ch01.A")
    // println("className ${a.name}")

    // callAll()
    // val a = A()::class.java
    // println("className ${a.name}")
}

fun callNon() {

}

fun callStaticOnly() {
    val a = Class.forName("me.proffl.ch01.ReflectionMethodsKt$A")
    println("className ${a.name}")
}

fun callAll() {
    val a = A()::class.java
    println("className ${a.name}")
}
