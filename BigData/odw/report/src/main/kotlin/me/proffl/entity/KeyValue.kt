package me.proffl.entity


data class KeyValue<T, U>(
    var key: T? = null,
    var value: U? = null
) {
}