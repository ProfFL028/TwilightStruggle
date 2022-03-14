package me.proffl.entity


data class ReportCell(
    var sheetIdx: Int = -1,
    var sheetName: String = "",
    var rowIdx: Int = 0,
    var colIdx: Int = 0,
    var expandRow: Boolean = false,
    var expandCol: Boolean = false,
    var dataset: Dataset? = null
) {
}