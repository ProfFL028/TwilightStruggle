package com.proffl.flink.app

import com.proffl.flink.model.SensorReading
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import java.time.LocalDate
import java.time.temporal.ChronoField
import java.time.temporal.Temporal
import java.time.temporal.TemporalField

class CollectionSourceApp {
}

fun main() {
    var env = StreamExecutionEnvironment.getExecutionEnvironment()
    var sensor = env.fromCollection(arrayListOf(
        SensorReading("Sensor_1", LocalDate.now().toEpochDay(), 30.5),
        SensorReading("Sensor_5", LocalDate.now().toEpochDay(), 32.5),
        SensorReading("Sensor_6", LocalDate.now().toEpochDay(), 34.5),
        SensorReading("Sensor_2", LocalDate.now().toEpochDay(), 31.5)
    ))
    sensor.print("sensor")

    var ints = env.fromElements(1,2,3,5,7,8)
    ints.print("ints")

    env.execute()

}