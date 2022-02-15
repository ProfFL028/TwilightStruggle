package com.proffl.entity.poi

import org.apache.poi.ss.usermodel.Cell
import org.apache.poi.ss.usermodel.CellType
import org.apache.poi.ss.usermodel.Row
import java.lang.reflect.Field
import java.util.*

class PoiRowToEntity {
    companion object {
        fun <T> rowToEntity(row: Row, clz: Class<T>, relIdx: Int=0):T {
            val obj = clz.newInstance()
            for (field in clz.declaredFields) {
                field.isAccessible = true

                if (field.getDeclaredAnnotation(XlsxField::class.java) != null) {
                    val fieldAnnotation = field.getDeclaredAnnotation(XlsxField::class.java) as XlsxField
                    setField(obj, field, row.getCell(fieldAnnotation.columnIndex + relIdx))
                } else if (field.getDeclaredAnnotation(XlsxCompositeField::class.java) != null) {
                    var compositeField =  field.getDeclaredAnnotation(XlsxCompositeField::class.java)
                    val newRelIdx = if (compositeField.rel) relIdx + compositeField.from else 0
                    val fieldClz = field.type
                    val subObj = rowToEntity(row, fieldClz, newRelIdx)
                    field.set(obj, subObj)
                }
            }

            return obj
        }

        private fun <T> setField(obj: T, field: Field, cell: Cell) {
            when (cell.cellType) {
                CellType.STRING -> {
                    if (field.type != String::class.java)
                        field.set(obj, excelCellToBean(cell.stringCellValue, field.type))
                    else {
                        field.set(obj, cell.stringCellValue)
                    }
                }
                CellType.NUMERIC -> {
                    if (field.type == String::class.java) {
                        field.set(obj, cell.numericCellValue.toString())
                    } else if (field.type == Int::class.java) {
                        field.set(obj, cell.numericCellValue.toInt())
                    } else if (field.type == Boolean::class.java) {
                        field.set(obj, cell.numericCellValue.toInt() == 1)
                    } else {
                        field.set(obj, cell.numericCellValue)
                    }
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

        private fun excelCellToBean(serial: String, type: Class<*>?): Any? {
            if (type == Int::class.java) {
                var res = 0
                try {
                    res = Integer.parseInt(serial)
                } catch (e: Exception) {
                    println(e.message)
                }
                return res
            } else if (type == Boolean::class.java) {
                return serial.lowercase(Locale.getDefault()) == "true" || serial.trim() == "1"
            }
            return null
        }
    }
}