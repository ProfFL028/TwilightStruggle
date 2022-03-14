package me.proffl.core

import me.proffl.entity.KeyValue
import me.proffl.entity.Report
import me.proffl.entity.ReportCell
import org.slf4j.LoggerFactory

/**
 *
 */

enum class TemplateParserStatus {
    Begin, Var, Sql, Use, Set
}

enum class ParseSetStatus {
    Begin, RowIdx, Expand, Data
}

class TemplateParser(var lines: List<String>) {

    companion object {
        private val logger = LoggerFactory.getLogger(TemplateParser::class.java)
    }

    private var idx: Int = 0
    private var parserStatus = TemplateParserStatus.Begin

    fun parse(): Report {
        val report = Report()
        while (idx < lines.size) {
            val line = lines[idx]
            when (parserStatus) {
                TemplateParserStatus.Begin -> if (line.startsWith("var")) {
                    parserStatus = TemplateParserStatus.Var
                    report.addVar(parseVar())
                } else if (line.startsWith("sql")) {
                    parserStatus = TemplateParserStatus.Sql
                    report.addSql(parseSql())
                } else if (line.startsWith("set")) {
                    parserStatus = TemplateParserStatus.Set
                    report.addCell(parseSet())
                } else if (line.startsWith("use")) {
                    parserStatus = TemplateParserStatus.Use
                    report.setSheet(parseUse())
                }
            }
        }
        return report
    }

    private fun parseSet(): ReportCell {
        val line = lines[idx].substring(4).trim()
        val reportCell = ReportCell()
        var parseSetStatus = ParseSetStatus.Begin

        var idx = 0
        while (idx < line.length) {
            when (parseSetStatus) {
                ParseSetStatus.Begin -> {
                    var c = line[idx]
                    var colIdx = 0
                    while (c.isLetter() && idx < line.length) {
                        var t = c - 'A'
                        if (t !in 0..25) {
                            t = c - 'a'
                        }
                        colIdx = colIdx * 26 + t
                        c = line[++idx]
                    }
                    if (c.isDigit()) {
                        reportCell.colIdx = colIdx
                        parseSetStatus = ParseSetStatus.RowIdx
                    } else {
                        logger.error("Invalid Input: $line")
                        throw IllegalArgumentException(line)
                    }
                }
                ParseSetStatus.RowIdx -> {
                    var c = line[idx]
                    var rowIdx = 0
                    while (c.isDigit() && idx < line.length) {
                        rowIdx = rowIdx * 10 + (c - '0')
                        c = line[++idx]
                    }
                    reportCell.rowIdx = rowIdx

                    if (c == '!' || c == '>') {
                        parseSetStatus = ParseSetStatus.Expand
                    } else {
                        while (c == ' ' && idx < line.length) {
                            c = line[++idx]
                        }
                        if (c == '=') {
                            parseSetStatus = ParseSetStatus.Data
                        } else {
                            throw IllegalArgumentException(line)
                        }
                    }
                }
                ParseSetStatus.Expand -> {
                    if (line[idx] == '!') {
                        reportCell.expandCol = true
                        ++idx
                    } else if (line[idx] == '>') {
                        reportCell.expandRow = true
                        ++idx
                    }
                    if (line[idx] == '!' || line[idx] == '>') continue
                    while (line[idx] == ' ' && idx < line.length) ++idx
                    if (line[idx] == '=') {
                        parseSetStatus = ParseSetStatus.Data
                    } else {
                        throw IllegalArgumentException(line)
                    }
                }
                ParseSetStatus.Data -> {
                    idx++
                    while (idx < line.length && line[idx] == ' ') ++idx
                    val dataset = StringBuilder()
                    
                }
            }
        }


        return reportCell
    }

    private fun parseSql(): KeyValue<String, String> {

    }

    private fun parseVar(): KeyValue<String, String> {
        val line = lines[idx].substring(4).trim()
        val tokens = line.split("=")
        val keyValue = KeyValue<String, String>()
        if (tokens.size > 1) {
            keyValue.key = tokens[0].trim()

            val valueBuilder = StringBuilder()
            for (i in 1 until tokens.size) {
                valueBuilder.append(tokens[i])
            }
            keyValue.value = tokens[1].trim()
        }

        return keyValue
    }

}
