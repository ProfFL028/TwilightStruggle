package me.proffl.entity

data class Dataset(
    var name: String = "",
    var rowName: String = "",
    var colName: String = ""
) {
    companion object {
        /**
         * parse dataset like data1[x][y]
         */
        fun from(expr: String): Dataset {
            val dataset = Dataset()
            var tokenBuilder = StringBuilder()
            var i = 0
            while (i < expr.length && expr[i] != '[') {
                tokenBuilder.append(expr[i])
                ++i
            }
            dataset.name = tokenBuilder.toString()
            tokenBuilder = StringBuilder()
            ++i // skip [
            while (i < expr.length && expr[i] != ']') {
                tokenBuilder.append(expr[i])
                ++i
            }
            dataset.rowName = tokenBuilder.toString()
            ++i // skip ]
            ++i // skip [

            tokenBuilder.toString()
            while (i < expr.length && expr[i] != ']') {
                tokenBuilder.append(expr[i])
                ++i
            }
            dataset.colName = tokenBuilder.toString()
            return dataset
        }
    }

    override fun toString(): String {
        if (name.isEmpty()) {
            return ""
        }
        return "$name[${rowName}][$colName]"
    }
}