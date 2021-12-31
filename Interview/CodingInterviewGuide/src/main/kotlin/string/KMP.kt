package string

/**
 * @content search a string contains another string. Time requires O(m+n)
 *
 * @level 4
 */
class KMP {
    companion object {
        fun find(str1: String, str2:String): Int {
            if (str1.isEmpty() || str2.isEmpty()) {
                return -1
            }
            var s1i = 0
            var s2i = 0
            var next = getNextArray(str2)
            while (s1i < str1.length && s2i < str2.length) {
                if (str1[s1i] == str2[s2i]) {
                    s1i += 1
                    s2i += 1
                } else if (next[s2i] == -1) {
                    s1i += 1
                } else {
                    s2i = next[s2i]
                }
             }
            return if (s2i == str2.length) s1i - s2i else -1
        }

        fun getNextArray(str: String): IntArray {
            if (str.isEmpty()) {
                return IntArray(1) {-1}
            }
            var next = IntArray(str.length)
            next[0] = -1
            next[1] = 0
            var pos = 2
            var cn = 0
            while (pos < str.length) {
                if (str[pos - 1] == str[cn]) {
                    cn += 1
                    next[pos] = cn
                    pos += 1
                } else if (cn > 0) {
                    cn = next[cn]
                } else {
                    next[pos] = 0
                    pos += 1
                }
            }
            return next
        }
    }
}

fun main() {
    var str1 = "6,1,12,0,3,10,13,#,#,#,#,4,14,20,16,2,5,11,15"
    var str2 = "4,14,20,16,2,5,11,#"
    println(KMP.find(str1, str2))
    str2 = "4,14,20,16,2,5,11,15"
    println(KMP.find(str1, str2))

    for (i in KMP.getNextArray(str2)) {
        print("$i ")
    }
    println()

    for(i in KMP.getNextArray("abcabcabc")) {
        print("$i ")
    }
    println()
    for(i in KMP.getNextArray("abcabcabcaa")) {
        print("$i ")
    }
    println()
}
