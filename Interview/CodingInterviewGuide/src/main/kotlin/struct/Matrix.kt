package struct

import java.text.NumberFormat

class Matrix {
    var rowCount: Int
    var colCount: Int
    var datas: Array<IntArray>

    constructor(rowCount: Int, colCount: Int, dataStr: String) {
        this.rowCount = rowCount
        this.colCount = colCount
        this.datas = Array(rowCount) { IntArray(colCount) }
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

    fun pow(n: Int): Matrix {
        var result = Matrix(this.rowCount, this.colCount, "")
        var tmp = Matrix(this.rowCount, this.colCount, "")
        result.copy(this)
        tmp.copy(this)

        var cur = n
        while (cur > 1) {
            // TODO: implement power(2)
        }
        return result
    }

    fun copy(matrix: Matrix): Matrix {
        this.rowCount = matrix.rowCount
        this.colCount = matrix.colCount
        this.datas = Array(this.rowCount) {IntArray(this.colCount)}
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
}
