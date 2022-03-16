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
        sql[key]= value
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


}

