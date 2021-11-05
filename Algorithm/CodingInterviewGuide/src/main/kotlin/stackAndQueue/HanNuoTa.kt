package stackAndQueue

import java.lang.RuntimeException

class HanNuoTa {
    var hnt1 = ArrayDeque<Int>()
    var hnt2 = ArrayDeque<Int>()
    var hnt3 = ArrayDeque<Int>()
    var num = 0

    constructor(n: Int) {
        this.num = n
        for (i in 0..this.num)
            this.hnt1.add(i)
    }

    fun moveAToC(n: Int) {
        when (n) {
            1 -> {
                println("move 1 from a to c")
            }
            2 -> {
                println("move 1 from a to b")
                println("move 2 from a to c")
                println("move 1 from b to c")
            }
            else -> {
                moveAToC(n - 2)
                println("move ${n - 1} from a to b")
                moveCToB(n - 2)
                println("move $n from a to c")
                moveBToC(n - 1)
            }
        }
    }
    fun moveAToB(n: Int) {
        when (n) {
            1 -> println("move 1 from a to b")
            2 -> {
                println("move 1 from a to c")
                println("move 2 from a to b")
                println("move 1 from c to b")
            }
            else -> {
                moveAToB(n - 2)
                println("move ${n - 1} from a to b")
                moveBToC(n - 2)
                println("move $n from a to b")
                moveCToB(n - 1)
            }
        }
    }
    fun moveBToC(n: Int) {
        when (n) {
            1 -> {
                println("move 1 from b to c")
            }
            2 -> {
                println("move 1 from b to a")
                println("move 2 from b to c")
                println("move 1 from a to c")
            }
            else -> {
                moveBToC(n - 2)
                println("move ${n - 1} from b to a")
                moveCToA(n - 2)
                println("move $n from b to c")
                moveAToC(n - 1)
            }
        }
    }
    fun moveBToA(n: Int) {
        when (n) {
            1 -> {
                println("move 1 from b to a")
            }
            2 -> {
                println("move 1 from b to c")
                println("move 2 from b to a")
                println("move 1 from c to a")
            }
            else -> {
                moveBToA(n - 2)
                println("move ${n - 1} from b to c")
                moveAToC(n - 2)
                println("move $n from b to a")
                moveCToA(n - 1)
            }
        }
    }
    fun moveCToB(n: Int) {
        when (n) {
            1 -> {
                println("move 1 from c to b")
            }
            2 -> {
                println("move 1 from c to a")
                println("move 2 from c to b")
                println("move 1 from a to b")
            }
            else -> {
                moveCToB(n - 2)
                println("move ${n - 1} from c to a")
                moveBToA(n - 2)
                println("move $n from c to b")
                moveAToC(n - 1)
            }
        }
    }
    fun moveCToA(n: Int) {
        when (n) {
            1 -> {
                println("move 1 from c to a")
            }
            2 -> {
                println("move 1 from c to b")
                println("move 2 from c to a")
                println("move 1 from b to a")
            }
            else -> {
                moveCToA(n - 2)
                println("move ${n - 1} from c to b")
                moveAToB(n - 2)
                println("move $n from c to a")
                moveBToA(n - 1)
            }
        }
    }
}

fun main() {
    var hnt = HanNuoTa(5)
    hnt.moveAToC(5)
}
