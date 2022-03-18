package me.proffl.reg.example

import me.proffl.util.RegUtils

fun main() {
    fun printResult(regStr: String, str: String) {
        val result = RegUtils.match(regStr, str)

        if (result != null) {
            println("$regStr matching $str result: ${result.groups}")
        } else {
            println("$regStr doesn't matching $str ")
        }
    }

    // we need to wrap `\` before special characters.
    val str = "a.b?"
    val reg = "a\\.b\\?"
    printResult(reg, str)

    val str2 = "{food}"
    val reg2 = "\\{food\\}"
    printResult(reg2, str2)

    // and we don't need to add `\` inside character class, except ^, -, ] and \
    val  reg3 = "^[@%*+$#?.]+$"
    val str3 = "@#%$.*"
    printResult(reg3, str3)
    val reg4 = "^[a-zA-Z0-9.\\-\\\\]+$"
    val str4 = "xyzTR-4.5\\00"
    printResult(reg4, str4)

    // any literally between \Q and \E will avoid escaping
    printResult("\\Q^*+.\\E", "^*+.")
    printResult("\\Q[0-9a-z]\\E", "[0-9a-z]")

    // predefined shorthand character class
    /**
     * \d [0-9]
     * \D [^\d]
     * \w [a-zA-Z0-9_]
     * \W [^\w]
     * \s [ \t\r\n\f\x0B]
     * \S [^\s]
     * \h horizontal whitespace character [ \t\xA0\u1680\u180e\u2000-\u200a\u202f\u205f\u3000]
     * \H not \h
     * \v vertical whitespace character [\n\x0B\f\r\x85\u2028\u2029]
     * \V non-vertical whitespace character
     */
    // predefined POSIX character classes
    /**
     * \p{ASCII} [\x00-\x7F]
     * \p{Digit} [0-9]
     * \p{Lower} [a-z]
     * \p{Upper} [A-Z]
     * \p{Alpha} [\p{Lower}\p{Upper}]
     * \p{Alnum} [\p{Lower}\p{Upper}\p{Digit}]
     * \p{Punct} [!"\#$%&'()*+,-./:;<=>?@\[\\\]^_\{|}~]
     * \p{Blank} [ \t]
     * \p{Space} [ \t\n\x0B\f\r]
     * \p{Graph} [\p{Alnum}\p{Punct}]
     * \p{Pirnt}[\p{Graph}\x20]
     * \p{Cntrl}[\x00-\x1F\x7F]
     * \p{Xdigit} hexadecimal digit [0-9a-fA-F]
     */

    // predefined
    /**
     * \p{javaLowerCase}
     * \p{javaUpperCase}
     * \p{javaWhitespace}
     * \p{javaMirrored}
     */

    // unicode support
    /**
     * \p{L} any letter from any language
     * \p{Lu} uppercase letter
     * \p{Ll} lowercase letter
     * \p{N} digit
     * \p{P} punctuation letter
     * \p{Z} whitespace or invisible separator
     * \p{C} invisible control letter
     * \p{Sc} currency symbol
     * \R recommended to use \R to match any newline character even if dealing with ASCII text
     *
     * \P{property} not \p
     */
}