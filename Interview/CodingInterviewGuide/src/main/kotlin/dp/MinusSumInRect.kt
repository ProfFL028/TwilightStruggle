package dp

import struct.Matrix
import kotlin.math.min

/**
 * Given a Rectangle, find the minus path from top-left to down-right.
 *
 * @level 2
 */
class MinusSumInRect {
    companion object {
        fun minusSum(m: Matrix): Int {
            var fromRowToCol = m.rowCount >= m.colCount
            var less = if (fromRowToCol) m.colCount else m.rowCount
            var more = if (!fromRowToCol) m.colCount else m.rowCount
            var tmp = Array(less) {0}
            tmp[0] = m.datas[0][0]
            for(i in 1 until less) {
                tmp[i] = tmp[i - 1] + if (fromRowToCol) m.datas[0][i] else m.datas[i][0]
            }
            for (i in 1 until less) {
                tmp[0] += if (fromRowToCol) m.datas[i][0] else m.datas[0][i]
                for (j in 1 until more) {
                    var minus = min(tmp[j-1], tmp[j])
                    tmp[j] = minus +  if (fromRowToCol) m.datas[i][j] else m.datas[j][i]
                }
            }
            return tmp[less - 1]
        }
    }

}

fun main() {
    var matrix = Matrix(4, 4, "1,3,5,9,8,1,3,4,5,0,6,1,8,8,4,0")
    println(MinusSumInRect.minusSum(matrix))
}
