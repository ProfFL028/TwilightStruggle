package me.proffl.entity

import me.proffl.entity.poi.XlsxField
import me.proffl.entity.poi.XlsxSheet
import javax.persistence.Column

class ColumnType {
    companion object {
        const val VARCHAR = "VARCHAR"
        const val BIGINT = "BIGINT"
        const val DOUBLE = "DOUBLE"
        const val INTEGER = "INTEGER"
        const val SMALLINT = "SMALLINT"
        const val TIMESTAMP = "TIMESTAMP"
        const val CHARACTER = "CHARACTER"
        const val CHAR = "CHAR"
        const val DATE = "DATE"
        const val TIME = "TIME"
    }
}

@XlsxSheet(value = "ColumnMetadata")
data class ColumnMetadata(
    @XlsxField(columnIndex = 3)
    var code: String = "",
    @XlsxField(columnIndex = 4)
    var name: String = "",
    @XlsxField(columnIndex = 5)
    var type: String = "",
    @XlsxField(columnIndex = 6)
    var length: Int = 0,
    @XlsxField(columnIndex = 7)
    var precision: Int = 0,
    @XlsxField(columnIndex = 8)
    var isDeliver: Boolean = false,
    @XlsxField(columnIndex = 9)
    var isUsed: Boolean = false,
    @XlsxField(columnIndex = 10)
    var isPrimaryKey: Boolean = false,
    @XlsxField(columnIndex = 11)
    var description: String = "",
    @XlsxField(columnIndex = 12)
    var remark: String = "",
    @XlsxField(columnIndex = 13)
    var modifyDesc: String = "",
    @XlsxField(columnIndex = 14)
    var isSendToCZ: Boolean = false

) {
    override fun toString(): String {
        return "$code($name) $type($length, $precision)"
    }

    fun toSql(): String {
        return when (type) {
            ColumnType.BIGINT -> "$columnNameInSql BIGINT($length)"
            ColumnType.DOUBLE -> "$columnNameInSql DECIMAL($length, $precision)"
            ColumnType.INTEGER -> "$columnNameInSql INT"
            ColumnType.SMALLINT -> "$columnNameInSql SMALLINT"
            ColumnType.VARCHAR -> "$columnNameInSql VARCHAR($length)"
            ColumnType.TIMESTAMP -> "$columnNameInSql TIMESTAMP"
            ColumnType.CHARACTER, ColumnType.CHAR -> "$columnNameInSql CHARACTER($length)"
            ColumnType.DATE -> "$columnNameInSql DATE"
            ColumnType.TIME -> "$columnNameInSql TIME"
            else -> {
                println("$type is not supported!!!")
                return ""
            }
        }
    }

    private val columnNameInSql: String
        get() = this.code
}
