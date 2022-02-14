package com.proffl.entity.poi

import org.apache.logging.log4j.Logger
import org.apache.poi.ss.usermodel.Cell
import org.apache.poi.ss.usermodel.CellType
import org.apache.poi.ss.usermodel.Row
import java.lang.reflect.Field

class PoiRowToEntity {
    companion object {
        fun <T> rowToEntity(row: Row, clz: Class<T>):T {
            var obj = clz.newInstance()
            for (field in clz.declaredFields) {
                var fieldAnnotation = field.getDeclaredAnnotation(XlsxField::class.java) as XlsxField
                field.isAccessible = true
                setField(obj, field, row.getCell(fieldAnnotation.columnIndex))
            }

            return obj
        }

        private fun <T> setField(obj: T, field: Field, cell: Cell) {
            when (cell.cellType) {
                CellType.STRING -> {
                    field.set(obj, cell.stringCellValue)
                }
                CellType.NUMERIC -> {
                    field.set(obj, cell.numericCellValue)
                }
                CellType.BOOLEAN -> {
                    field.set(obj, cell.booleanCellValue)
                }
                CellType.FORMULA -> {
                    when (cell.cachedFormulaResultType) {
                        CellType.STRING -> {
                            field.set(obj, cell.richStringCellValue.toString())
                        }
                        CellType.NUMERIC -> {
                            field.set(obj, cell.numericCellValue)
                        }
                        else -> {
                            println("unknown formula type in cell: $cell")
                        }
                    }
                }
                CellType.ERROR -> {
                    println("cell type error in cell: $cell")
                }
            }
        }
    }
}