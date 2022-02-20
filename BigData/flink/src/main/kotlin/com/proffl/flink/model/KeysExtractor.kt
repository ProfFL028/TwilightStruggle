package com.proffl.flink.model

import java.math.BigDecimal

class KeysExtractor {
    companion object {
        fun getKey(keyNames: List<String>, obj: Any): String {
            val sb = StringBuilder("{")
            if (keyNames.isNotEmpty()) {
                val it = keyNames.iterator()
                appendKeyValue(sb, obj, it.next())
                while (it.hasNext()) {
                    sb.append(";")
                    appendKeyValue(sb, obj, it.next())
                }
            }
            sb.append("}")
            return sb.toString()
        }

        private fun appendKeyValue(sb: StringBuilder, obj: Any, fieldName: String) {
            sb.append(fieldName)
            sb.append("=")
            sb.append(FieldsExtractor.getFieldAsString(obj, fieldName))
        }
    }
}

class FieldsExtractor {
    companion object {
        fun getFieldAsString(obj: Any, fieldName: String): String {
            val clz = obj::class.java
            val field = clz.getDeclaredField(fieldName)
            field.isAccessible = true
            return field.get(obj).toString()
        }

        fun getDoubleByName(obj: Any, fieldName: String): Double {
            val field = obj::class.java.getField(fieldName)
            return field.getDouble(obj)
        }

        fun getBigDecimalByName(obj: Any, fieldName: String): BigDecimal {
            val field = obj::class.java.getField(fieldName)
            return BigDecimal(field.get(obj).toString())
        }

        fun <T> getByKeyAs(obj: Any, keyName: String): T {
            val field = obj::class.java.getField(keyName)
            return field.get(obj) as T
        }

    }
}