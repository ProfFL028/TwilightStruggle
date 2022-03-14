package me.proffl.entity


class TableMetadata(
    var systemName: String ="",
    var tableCode: String ="",
    var tableName: String ="",
) {
    var columnMetadataList: MutableList<ColumnMetadata> = ArrayList()

    fun addColumn(columnMetadata: ColumnMetadata) {
        this.columnMetadataList.add(columnMetadata)
    }

    fun toSqlSimple():String {
        return """ CREATE TABLE ods_${systemName}_$tableCode(
            ${columnsToSql()}
        )
        """.trimIndent()
    }
    private fun columnsToSql(): String {
        var sb = StringBuilder()
        for (columnMetadata in columnMetadataList) {
            sb.append(columnMetadata.toSql()).append(",\n")
        }
        return if (sb.isNotEmpty()) {
            sb.substring(0,sb.length - 2).toString()
        } else {
            ""
        }
    }

    fun toSqlComment(): String {
        return ""
    }

    fun toSqlAll(): String {
        return ""
    }
}