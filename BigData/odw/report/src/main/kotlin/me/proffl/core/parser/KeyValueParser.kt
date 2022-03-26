package me.proffl.core.parser

import me.proffl.entity.KeyValue

/**
 * Parse expression a=b to a KeyValue where key=a and value=b
 */
class KeyValueParser {

    companion object {
        fun parse(expr: String): KeyValue<String, String> {
            val token = expr.split("=")
            val keyValue = KeyValue<String, String>()
            if (token.size == 2) {
                keyValue.key = token[0].trim()
                keyValue.value = token[1].trim()
            } else {
                throw IllegalArgumentException("cannot parse $expr")
            }

            return keyValue
        }
    }
}