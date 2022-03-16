package me.proffl.core

import me.proffl.core.parser.KeyValueParser
import me.proffl.core.parser.ParserContext
import me.proffl.core.parser.expr.Expression
import me.proffl.core.parser.expr.ExpressionFactory
import me.proffl.entity.Dataset
import me.proffl.entity.KeyValue
import me.proffl.entity.Report
import me.proffl.entity.ReportCell
import org.slf4j.LoggerFactory

/**
 *
 */
class TemplateParser {

    companion object {
        private val logger = LoggerFactory.getLogger(TemplateParser::class.java)
    }

    fun parse(lines: List<String>): Report {
        val report = Report()
        val context = ParserContext(lines, 0)
        while (!context.isEnd()) {
            val line = context.next()
            val expr = ExpressionFactory.from(line)
            if (expr.type == "sql") {
                ExpressionFactory.append(expr, context)
            }
            addToReport(report, expr)
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
