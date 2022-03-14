package me.proffl.entity

import me.proffl.entity.poi.XlsxCompositeField
import me.proffl.entity.poi.XlsxField
import me.proffl.entity.poi.XlsxSheet

@XlsxSheet("标准化字段")
class TableRow(
    @XlsxField(columnIndex = 0)
    var systemName: String ="",
    @XlsxField(columnIndex = 1)
    var tableCode: String ="",
    @XlsxField(columnIndex = 2)
    var tableName: String ="",
    @XlsxCompositeField(from=3, to=14, rel=false)
    var columnMetadata: ColumnMetadata = ColumnMetadata()
) {
    companion object {
        const val TABLE_BEGIN_FLAG = "ALL"
    }

    override fun toString(): String {
        return "[$systemName].[$tableCode]($tableName):${columnMetadata}"
    }
}