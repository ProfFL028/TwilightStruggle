package me.proffl.entity

import me.proffl.core.parser.expr.Expression

enum class ReportFrequency {
    Day, Week, Month, Quad, Year
}

data class Report(
    var name: String = "",
    var templateFileName: String = "",
    var frequency: ReportFrequency = ReportFrequency.Day
) {
    fun addVar(key: String, value: String) {
        vars[key] = value
    }

    fun addSql(key: String, value: String) {
        sql[key]= value.replace("\"\"\"", "")
    }

    fun addCell(cell: ReportCell) {
        if (currentSheet.toIntOrNull() == null) {
            cell.sheetName = currentSheet
        } else {
            cell.sheetIdx = currentSheet.toInt()
        }
        cells.add(cell)
    }

    fun setSheet(sheetName: String) {
        currentSheet = sheetName
    }

    private var currentSheet: String = ""

    private val sql: MutableMap<String, String> = HashMap()
    private val cells: MutableList<ReportCell> = ArrayList()
    private val vars: MutableMap<String, String> = HashMap()

    override fun toString(): String {
        val builder = StringBuilder()
        builder.appendLine("report name: $name {")
        builder.appendLine("\tvars: [")
        for (v in vars) {
            builder.appendLine("\t\t${v.key}=${v.value}")
        }
        builder.appendLine("\t] cells: [")
        for (c in cells) {
            if (c.sheetIdx !=-1) {
                builder.append("\t\tsheetId: ${c.sheetIdx} ")
            } else {
                builder.append("\t\tsheetName: ${c.sheetName} ")
            }
            builder.appendLine("${c.rowIdx}_${c.colIdx}=${c.dataset} expandRow: ${c.expandRow} expandCol: ${c.expandCol}")
        }
        builder.appendLine("\t] sqls: [")
        for (s in sql) {
            builder.appendLine("${s.key} =  ${s.value}")
        }
        builder.appendLine("]")
        return builder.toString()
    }
}

