package com.proffl.flink.source

import com.proffl.flink.model.SensorReading
import org.apache.flink.streaming.api.functions.source.SourceFunction
import java.time.LocalDateTime
import java.util.*
import kotlin.collections.HashMap

class SensorSource: SourceFunction<SensorReading> {
    var running = true
    override fun run(ctx: SourceFunction.SourceContext<SensorReading>) {
        var sensors = HashMap<String, Double>()
        var random = Random(0)
        for (i in 0 until 10) {
            sensors["sensor_$i"] = random.nextGaussian() * 20 + 60
        }

        while (running) {
            for (sensor in sensors.keys) {
                var newTemp = sensors.getValue(sensor) + random.nextGaussian()
                sensors[sensor] = newTemp
                ctx.collect(SensorReading(sensor, System.currentTimeMillis(), newTemp))
            }
            Thread.sleep(1000L)
        }
    }

    override fun cancel() {
        running = false
    }
}