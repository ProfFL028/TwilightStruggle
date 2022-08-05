package string

/**
 * check if characters in a string disappear only once.
 */
fun isUnique(s: String): Boolean {
    val set = HashSet<Char>()
    for (c in s.toCharArray()) {
        if (set.contains(c)) {
            return false
        }
    }
    return true
}


fun main() {
    val s1 = "aaaa"
    val s2 = "abc"
    println("$s1 is unique? ${isUnique(s1)}")
    println("$s2 is unique? ${isUnique(s2)}")
}