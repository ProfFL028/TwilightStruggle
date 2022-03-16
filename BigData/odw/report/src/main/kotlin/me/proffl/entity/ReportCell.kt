package me.proffl.entity

import me.proffl.core.parser.expr.Expression


data class ReportCell(
    var sheetIdx: Int = -1,
    var sheetName: String = "",
    var rowIdx: Int = 0,
    var colIdx: Int = 0,
    var expandRow: Boolean = false,
    var expandCol: Boolean = false,
    var dataset: Dataset? = null
) {
    companion object {
        fun from(expr: Expression): ReportCell {
            val cell = ReportCell()
            cell.colIdx = 0
            var i = 0
            while (i < expr.key.length && expr.key[i].isLetter()) {
                cell.colIdx = cell.colIdx * 26 + (expr.key[i] - 'A')
                ++i
            }
            cell.rowIdx = 0
            while (i < expr.key.length && expr.key[i].isLetter()) {
                cell.colIdx = cell.colIdx * 10 + (expr.key[i] - '0')
                ++i
            }
            cell.expandCol = expr.key.contains('!')
            cell.expandRow = expr.key.contains('>')

            val dataset = Dataset.from(expr.value)
            cell.dataset = dataset
            return cell
        }
    }
}