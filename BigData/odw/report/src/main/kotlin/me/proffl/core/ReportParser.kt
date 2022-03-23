package me.proffl.core

import me.proffl.core.parser.ParserContext
import me.proffl.core.parser.expr.Expression
import me.proffl.core.parser.expr.ExpressionFactory
import me.proffl.entity.Report
import me.proffl.entity.ReportCell
import org.slf4j.LoggerFactory

/**
 *
 */
class ReportParser {

    companion object {
        private val logger = LoggerFactory.getLogger(ReportParser::class.java)
    }

    fun parse(lines: List<String>): Report {
        val report = Report()
        val context = ParserContext(lines, 0)
        while (!context.isEnd()) {
            val line = context.next()
            try {
                val expr = ExpressionFactory.from(line)
                if (expr != null) {
                    if (expr.type == "sql") {
                        ExpressionFactory.append(expr, context)
                    }
                    addToReport(report, expr)
                }
            } catch (e: Exception) {
                logger.error("parsing error: ${e.message}")
            }
        }
        return report
    }

    private fun addToReport(report: Report, expr: Expression) {
        if (expr.type == "var")
            report.addVar(expr.key, expr.value)
        else if (expr.type == "sql")
            report.addSql(expr.key, expr.value)
        else if (expr.type == "use")
            report.setSheet(expr.key)
        else if (expr.type == "set") {
            val cell = ReportCell.from(expr)
            report.addCell(cell)
        }
    }
}
