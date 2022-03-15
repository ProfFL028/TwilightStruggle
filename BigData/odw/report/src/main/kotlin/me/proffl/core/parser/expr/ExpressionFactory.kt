package me.proffl.core.parser.expr

import me.proffl.core.parser.ParserContext

class ExpressionFactory {
    companion object {
        fun from(expr: String): Expression {
            val result = Expression()
            val tokens = expr.trim().split(" ", limit = 2)
            if (tokens.size == 2) {
                result.key = tokens[0].trim()
                val keyValueTokens = tokens[1].split("=")
                if (keyValueTokens.size == 2) {
                    result.key = keyValueTokens[0]
                    result.value= keyValueTokens[0]
                }
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