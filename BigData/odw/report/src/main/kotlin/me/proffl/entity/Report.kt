package me.proffl.entity

enum class ReportFrequency {
    Day, Week, Month, Quad, Year
}


data class Report(
    var name: String = "",
    var templateFileName: String = "",
    var frequency: ReportFrequency = ReportFrequency.Day
) {
    fun addVar(keyValue: KeyValue<String, String>) {
        if (keyValue.key != null) {
            vars[keyValue.key!!] = keyValue.value!!
        }
    }

    fun addSql(keyValue: KeyValue<String, String>) {
        if (keyValue.key != null) {
            sql[keyValue.key!!] = keyValue.value!!
        }
    }

    fun addCell(cell: ReportCell) {
        cells.add(cell)
    }

    private val sql: MutableMap<String, String> = HashMap()
    private val cells: MutableList<ReportCell> = ArrayList()
    private val vars: MutableMap<String, String> = HashMap()


}

