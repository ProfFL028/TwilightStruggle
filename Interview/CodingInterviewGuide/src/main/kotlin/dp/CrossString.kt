package dp

class CrossString {
    companion object {
        fun find(s1: String, s2: String, aim: String): Boolean {
            var s1Len = s1.length
            var s2Len = s2.length
            var aimLen = aim.length
            if (s1Len + s2Len != aimLen) {
                return false
            }
            if (s1Len < s2Len)
                return find(s2, s1, aim)

            var tmp = Array(s2.length + 1) { false }
            for (i in s2.indices) {
                tmp[i + 1] = s2[i] == aim[i]
                if (!tmp[i + 1])
                    break
            }
            for (i in 1..s1.length) {
                tmp[0] = tmp[0] && s1[i-1] == aim[i-1]
                for (j in 1 .. s2.length) {
                    tmp[j] = (s1[i-1] == aim[i + j - 1] && tmp[j])
                            || (s2[j-1] == aim[i + j - 1] && tmp[j - 1])
                }

            }
            return tmp[s2.length]
        }
    }
}

fun main() {
    var s1 = "AABBF"
    var s2 = "ABCDE"
    var aim = "AAABBBFCDE"
    println(CrossString.find(s1, s2, aim))
}
