package me.proffl.sink

import me.proffl.entity.Alert
import org.apache.flink.streaming.api.functions.sink.SinkFunction
import org.slf4j.LoggerFactory

class AlertLogSink: SinkFunction<Alert> {
    companion object {
        var logger = LoggerFactory.getLogger(AlertLogSink::class.java)
    }

    override fun invoke(value: Alert, context: SinkFunction.Context) {
        logger.info(value.toString())
    }
}