package me.proffl.entity

data class Alert(var id: Long=0L) {
    override fun toString(): String {
        return "id: $id"
    }
}