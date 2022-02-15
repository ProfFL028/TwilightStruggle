package com.proffl.job

import java.util.Properties

abstract class Job {
    abstract fun work()
    val properties = Properties()

    fun addProperties(key: String, value: String) {
        properties.setProperty(key, value)
    }
}