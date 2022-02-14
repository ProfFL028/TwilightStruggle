package com.proffl.entity

import com.proffl.entity.poi.XlsxField
import com.proffl.entity.poi.XlsxSheet

@XlsxSheet("CodeTable")
data class CodeTable(
    @XlsxField(0) var schemaName: String = "",
    @XlsxField(1) var tableName: String = "",
    @XlsxField(2) var columnName: String = "",
    @XlsxField(3) var code: String = "",
    @XlsxField(4) var mean: String = ""
) {
    override fun toString(): String {
        return "$schemaName.$tableName.$columnName['$code'] = $mean"
    }
}