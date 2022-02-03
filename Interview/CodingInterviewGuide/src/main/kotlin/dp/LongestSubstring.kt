package dp

/**
 * find the longest substring in two strings.
 *
 * @level 3
 */
class LongestSubstring {
    companion object {
        fun find(s1: String, s2: String): String {
            var result = ""
            var longest = 0
            var lastResult = ""
            var lastLongest = 0
            var i = 0
            var j = 0
            while ((i + longest) < s1.length) {
                lastResult = ""
                lastLongest = 0
                j = 0
                while ((j + longest) < s2.length && j < s2.length && i < s1.length) {
                    if (s1[i] == s2[j]) {
                        lastLongest++
                        lastResult += s2[j]
                        i++
                    } else {
                        if (lastLongest > longest) {
                            longest = lastLongest
                            result = lastResult
                        }
                        i -= lastLongest
                        j -= lastLongest
                        lastResult = ""
                        lastLongest = 0
                    }
                    j++
                }
                if (lastLongest > 0) {
                    i-= lastLongest
                    if (lastLongest > longest) {
                        longest = lastLongest
                        result = lastResult
                    }
                }
                i++
            }
            return result
        }
    }
}

fun main() {
    var s1 = "bebcde"
    var s2 = "abcdef"
    println(LongestSubstring.find(s1, s2))
}
