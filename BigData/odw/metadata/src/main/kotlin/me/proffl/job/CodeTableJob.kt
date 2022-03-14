package me.proffl.job

import me.proffl.entity.CodeTable
import me.proffl.entity.poi.PoiRowToEntity
import me.proffl.table.CodeTableTable
import org.apache.poi.hssf.usermodel.HSSFWorkbook
import java.io.File
import java.io.FileInputStream
import java.util.*

class CodeTableJob: Job() {
    companion object {
        const val CODE_TABLE_PATH = "codeTablePath"
    }

    override fun work() {
        var metaExcelPath = properties[CODE_TABLE_PATH].toString()
        var metaWorkbook = HSSFWorkbook(FileInputStream(File(metaExcelPath)))

        var codeTableTable = CodeTableTable()
        for (sheet in metaWorkbook.sheetIterator()) {
            for (row in sheet.rowIterator()) {
                var codeTable = PoiRowToEntity.rowToEntity(row, CodeTable::class.java)
                codeTableTable.add(codeTable)
            }
        }
    }
}