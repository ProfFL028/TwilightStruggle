package me.proffl.ch01

open class Base(str: String) {
    companion object {

        init {
            println("Base static method init1")
        }
        fun staticMethod() {
            println("static method in Base")
        }
        val staticMember1 = Base("member1")
        val staticMember2 = Base("member2")

        init {
            println("Base static method init2")
        }
    }

    init {
        println("constructor Base $str")
    }
}

class Derived(str: String) : Base(str) {
    companion object {
        init {
            println("Derived static method init2")
        }
        val staticMember2 = Derived("Member2")
        val staticMember1 = Derived("Member1")

        init {
            println("Derived static method init")
        }
    }

    init {
        println("constructor Derived $str")
    }
}


fun main() {
    val d = Derived("Hello world")
}