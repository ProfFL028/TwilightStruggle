package struct

import java.text.NumberFormat

class Matrix {
    var rowCount: Int
    var colCount: Int
    var datas: Array<IntArray>

    companion object {
        fun ones(rowCount: Int, colCount: Int): Matrix {
            var matrix = Matrix(rowCount, colCount, "")
            matrix.datas = Array(rowCount) { IntArray(colCount) { 1 } }
            return matrix
        }

        fun triangleOnes(n: Int):Matrix {
            var matrix = Matrix(n, n, "")
            for (i in 0 until n) {
                matrix.datas[i][i] = 1
            }

            return matrix
        }
    }

    constructor(rowCount: Int, colCount: Int, dataStr: String="") {
        this.rowCount = rowCount
        this.colCount = colCount
        this.datas = Array(rowCount) { IntArray(colCount) { 0 } }
        if (!dataStr.isEmpty()) {
            var datas = dataStr.split(",")
            var i = 0
            var j = 0
            for (data in datas) {
                this.datas[i][j] = Integer.parseInt(data)
                j++
                if (j >= this.colCount) {
                    j = 0
                    i++
                    if (i >= this.rowCount) {
                        break
                    }
                }
            }
        }
    }

    fun multi(matrix: Matrix): Matrix {
        if (this.colCount != matrix.rowCount) {
            throw IllegalArgumentException("can't multi [${this.rowCount}][${this.colCount}] with [${matrix.rowCount}][${matrix.colCount}]")
        }
        var result = Matrix(this.rowCount, matrix.colCount, "")
        for (i in 0 until this.rowCount) {
            for (j in 0 until matrix.colCount) {
                for (k in 0 until this.colCount) {
                    result.datas[i][j] += this.datas[i][k] * matrix.datas[k][j]
                }
            }
        }
        return result
    }

    fun pow(n: Int): Matrix {
        var result = triangleOnes(this.rowCount)
        var tmp = Matrix(this.rowCount, this.colCount, "")
        tmp.copy(this)

        var cur = n
        while (cur != 0) {
            if ((cur and 1) != 0) {
                result = result.multi(tmp)
            }
            tmp = tmp.multi(tmp)
            cur /= 2
        }
        return result
    }

    fun pow2(n: Int): Int {
        if (n == 0) {
            return 1
        }
        var cur = n
        var result = 1
        var tmp = 2
        while (cur != 0) {
            if ((cur and 1) != 0) {
                result *= tmp
            }
            tmp *= tmp
            cur /= 2
        }
        return result
    }

    fun copy(matrix: Matrix): Matrix {
        this.rowCount = matrix.rowCount
        this.colCount = matrix.colCount
        this.datas = Array(this.rowCount) { IntArray(this.colCount) }
        for (i in 0 until this.rowCount)
            for (j in 0 until this.colCount)
                this.datas[i][j] = matrix.datas[i][j]

        return this
    }

    override fun toString(): String {
        var title = "Matrix[$rowCount][$colCount]:${System.lineSeparator()}"
        var matString = ""
        for (row in datas) {
            matString = "$matString| "
            for (data in row) {
                matString += "${data.toString().padStart(4)}, "
            }
            matString = matString.substring(0, matString.length - 2) + " |${System.lineSeparator()}"
        }
        return title + matString
    }
}

fun main() {
    var matrix = Matrix(5, 5, "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25")
    println(matrix)

    for (i in 5 until 10) {
        println(matrix.pow2(i))
    }

    matrix = Matrix.ones(2, 2)
    matrix.datas[1][1] = 0

    var matrix2 = Matrix.ones(2, 2)
    matrix2.copy(matrix)
    for (i in 1 until 5) {
        matrix2 = matrix.multi(matrix2)
        println(matrix2)
    }

    var matrixN = matrix.pow(8)
    println(matrixN)
}
