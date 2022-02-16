package com.proffl.flink.config

data class Param<T>(
    var name: String,
    var type: Class<T>,
    var defaultValue: T
) {
    companion object {
        fun string(name: String, defaultValue: String): Param<String> {
            return Param(name, String::class.java, defaultValue)
        }

        fun integer(name: String, defaultValue: Int): Param<Int> {
            return Param(name, Int::class.java, defaultValue)
        }

        fun bool(name: String, defaultValue: Boolean): Param<Boolean> {
            return Param(name, Boolean::class.java, defaultValue)
        }
    }
}