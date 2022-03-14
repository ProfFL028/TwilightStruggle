package me.proffl.app

import me.proffl.entity.TableMetadata
import me.proffl.entity.TableRow
import me.proffl.entity.TableRow.Companion.TABLE_BEGIN_FLAG
import me.proffl.entity.poi.PoiRowToEntity
import org.apache.poi.hssf.usermodel.HSSFWorkbook
import java.io.File
import java.io.FileInputStream

fun main() {
    val path = "/tmp/doc/标准化文档-20220112/数据标准化拆分-场景二维码平台-发布版.xls"

    val tablesWorkbook = HSSFWorkbook(FileInputStream(File(path)))
    val tablesSheet = tablesWorkbook.getSheet("标准化字段")

    var rowIdx = 1
    var curTableMetadata: TableMetadata? = null
    while (rowIdx < tablesSheet.lastRowNum) {
        val tableRow = PoiRowToEntity.rowToEntity(tablesSheet.getRow(rowIdx)!!, TableRow::class.java)
        if (tableRow.columnMetadata.code.trim() == TABLE_BEGIN_FLAG) {
            if (curTableMetadata != null) {
                println(curTableMetadata.toSqlSimple())
                println("------------------------------")
            }
            curTableMetadata = TableMetadata(tableRow.systemName, tableRow.tableCode, tableRow.tableName)
        } else {
            curTableMetadata!!.addColumn(tableRow.columnMetadata)
        }
        rowIdx++
    }
    println(curTableMetadata!!.toSqlSimple())
}