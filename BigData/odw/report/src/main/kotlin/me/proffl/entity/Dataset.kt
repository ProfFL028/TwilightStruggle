package me.proffl.entity

data class Dataset(
    var name: String = "",
    var rowName: String = "",
    var colName: String = ""
) {
    companion object {
        fun from(expr: String):Dataset {
            val dataset = Dataset()

            return dataset
        }
    }
}