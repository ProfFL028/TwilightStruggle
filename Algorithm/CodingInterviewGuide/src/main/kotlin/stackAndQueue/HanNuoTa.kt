package stackAndQueue

import java.lang.RuntimeException

/**
 * 汉诺塔， https://en.wikipedia.org/wiki/Tower_of_Hanoi
 *
 */

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

    /**
     * 1。如果N是偶数，则1按ABCABC。。。顺序移动。如果N是奇数，则1按ACBACB顺序移动
     * 2。按顺序移动1
     * 3。移动非1所在两根柱子，（只能有一种可以移动的方式）
     * 4。如果没有全部到C柱子，回到第二步。
     */
    fun moveLikeACircle(n: Int) {
        if (n <= 0)
            throw RuntimeException("Error Input")

        var stacks = arrayListOf<ArrayDeque<Int>>()
        stacks.add(ArrayDeque())
        stacks.add(ArrayDeque())
        stacks.add(ArrayDeque())

        for (i in 1..n) {
            stacks[0].addFirst(i)
        }

        fun moveSingle(num: Int, from: Int, to: Int) {
            stacks[to].add(stacks[from].removeLast())
            println("move $num from $from to $to")
            println("------>stack0:${stacks[0]}")
            println("------>stack1:${stacks[1]}")
            println("------>stack2:${stacks[2]}")
        }

        var dest = if (n % 2 == 0) 2 else 1
        var onePosition = 0
        while (stacks[dest].size != n) {
            var prePosition = onePosition
            onePosition = (onePosition + 1) % 3
            moveSingle(1, prePosition, onePosition)
            if (stacks[dest].size == n) {
                break
            }

            when (onePosition) {
                0 -> {
                    val n1 = stacks[1].lastOrNull() ?: Int.MAX_VALUE
                    val n2 = stacks[2].lastOrNull() ?: Int.MAX_VALUE
                    if (n1 > n2) {
                        moveSingle(n2, 2, 1)
                    } else {
                        moveSingle(n1, 1, 2)
                    }
                }
                1 -> {
                    val n1 = stacks[0].lastOrNull() ?: Int.MAX_VALUE
                    val n2 = stacks[2].lastOrNull() ?: Int.MAX_VALUE
                    if (n1 > n2) {
                        moveSingle(n2, 2, 0)
                    } else {
                        moveSingle(n1, 0, 2)
                    }
                }
                2 -> {
                    val n1 = stacks[1].lastOrNull() ?: Int.MAX_VALUE
                    val n2 = stacks[0].lastOrNull() ?: Int.MAX_VALUE
                    if (n1 > n2) {
                        moveSingle(n2, 0, 1)
                    } else {
                        moveSingle(n1, 1, 0)
                    }
                }
            }
        }
    }

    fun moveLikeBinaryCode(n: Int) {
        if (n <= 0)
            throw RuntimeException("Error Input")

        var stacks = arrayListOf<ArrayDeque<Int>>()
        stacks.add(ArrayDeque())
        stacks.add(ArrayDeque())
        stacks.add(ArrayDeque())

        for (i in 1..n) {
            stacks[0].addFirst(i)
        }

        fun moveSingle(from: Int, to: Int) {
            var num = stacks[from].last()
            stacks[to].add(stacks[from].removeLast())
            println("move $num from $from to $to")
            println("------>stack0:${stacks[0]}")
            println("------>stack1:${stacks[1]}")
            println("------>stack2:${stacks[2]}")
        }

        var oddSteps = if(n % 2 == 0) arrayListOf(0, 1, 2) else arrayListOf(0, 2, 1)
        var evenSteps = if(n % 2 == 1) arrayListOf(0, 1, 2) else arrayListOf(0, 2, 1)

        var step = 1
        while (stacks[2].size != n) {
            var stepHalf = step % 2
            if (step % 2 == 0) {
                moveSingle(oddSteps[stepHalf % 3], oddSteps[(stepHalf + 1) % 3])
            } else {
                moveSingle(evenSteps[stepHalf % 3], evenSteps[(stepHalf + 1) % 3])
            }
            step++
        }
    }
}

fun main() {
    var hnt = HanNuoTa(5)
    // hnt.moveAToC(5)

    // hnt.moveLikeACircle(5)
    hnt.moveLikeACircle(5)
}
