package me.proffl.util

class ArrayUtils {
    companion object {
        fun format(byteArray: ByteArray): String {
            var result = StringBuilder("[")
            for (a in byteArray) {
                result.append(a.toInt().toString()).append(", ")
            }
            result.setLength(result.length - 2)
            result.append("]")
            return result.toString()
        }
    }
}