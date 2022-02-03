package dp

/**
 * give two strings and a cost function, find the minus cost for making these two string same.
 *
 * @level 3
 */
class MinusEditCost {
    companion object {
        fun find(s1: String, s2: String, ic: Int = 5, dc: Int = 3, rc: Int = 2): Int {
            if (s1.length < s2.length) {
                return find(s2, s1, ic, dc, rc)
            }

            var tmp = Array(s2.length + 1) { 0 }
            for (i in 1..s2.length) {
                tmp[i] = i * ic
            }
            for (i in s1.indices) {
                var leftUp = tmp[0]
                tmp[0] += dc
                for (j in s2.indices) {
                    var ec = if (s1[i] != s2[j]) rc else 0
                    var minEdit = minOf(leftUp + ec, tmp[j] + ic, tmp[1 + j] + dc)
                    leftUp = tmp[1 + j]
                    tmp[1 + j] = minEdit
                }
            }
            return tmp[s2.length]
        }
    }
}

fun main() {
    var s1 = "abcdf"
    var s2 = "ab12cd3"
    println(MinusEditCost.find(s1, s2))
}
