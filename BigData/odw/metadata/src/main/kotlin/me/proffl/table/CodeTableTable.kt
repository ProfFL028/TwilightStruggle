package me.proffl.table

import me.proffl.entity.CodeTable
import me.proffl.entity.CodeTable.Companion.CODE_TABLE_UNKOWN

class CodeTableTable {
    private var codeTables: MutableMap<String, CodeTable> = HashMap()

    fun add(codeTable: CodeTable) {
        codeTables[codeTable.hashKey()] = codeTable
    }

    fun remove(codeTable: CodeTable) {
        codeTables.remove(codeTable.hashKey())
    }

    fun value(schemaName: String, tableName: String, code: String): String {
        return codeTables.getOrDefault("$schemaName.$tableName.$code", CODE_TABLE_UNKOWN).mean
    }


}