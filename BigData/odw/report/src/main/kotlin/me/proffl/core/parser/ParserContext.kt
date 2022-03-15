package me.proffl.core.parser

data class ParserContext(
    var lines: List<String>,
    var idx: Int
) {
    fun isEnd(): Boolean {
        return idx < lines.size
    }
    fun next(): String {
        return lines[idx++]
    }
}