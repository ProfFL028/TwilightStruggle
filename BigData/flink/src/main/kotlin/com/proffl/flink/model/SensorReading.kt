package com.proffl.flink.model

class SensorReading(var sensorId:String="", var timestamp:Long=0L, var temperature:Double=0.0) {

    override fun toString(): String {
        return "$sensorId at $timestamp: [$temperature]"
    }
}