package me.proffl.core.parser.expr

import me.proffl.core.parser.ParserContext

class ExpressionFactory {
    companion object {
        /**
         * parsing expression like `type key=value`
         */
        fun from(expr: String): Expression? {
            val result = Expression()
            val exprCleaned = expr.trim()
            if (exprCleaned.isEmpty()) {
                return null
            }
            var tokenBuilder = StringBuilder()
            // find type first
            var i = 0
            while (i < exprCleaned.length && exprCleaned[i] != ' ') {
                tokenBuilder.append(exprCleaned[i])
                i++
            }
            if (i == exprCleaned.length) {
                throw IllegalArgumentException("$expr cannot be parsed!!")
            }
            result.type = tokenBuilder.toString()
            // remove blank spaces
            while (i < exprCleaned.length && exprCleaned[i] == ' ') {
                ++i
            }
            // find key
            tokenBuilder = StringBuilder()
            while (i < exprCleaned.length && exprCleaned[i] != '=') {
                if (exprCleaned[i] != ' ')
                    tokenBuilder.append(exprCleaned[i])
                ++i
            }
            result.key = tokenBuilder.toString()
            i++ // skip '='
            while (i < exprCleaned.length && exprCleaned[i] == ' ') {
                ++i
            }
            if (i < exprCleaned.length) {
                result.value = exprCleaned.substring(i)
            }
            return result
        }

        fun append(expr: Expression, context: ParserContext) {
            while (!context.isEnd()) {
                val line = context.next().trim()
                expr.value += line
                if (line.endsWith("\"\"\""))
                    break
            }
        }
    }
}