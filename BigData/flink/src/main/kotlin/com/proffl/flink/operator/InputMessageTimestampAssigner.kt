package com.proffl.flink.operator

import com.proffl.flink.model.InputMessage
import org.apache.flink.streaming.api.functions.AssignerWithPunctuatedWatermarks
import org.apache.flink.streaming.api.watermark.Watermark
import java.time.ZoneId
import javax.annotation.Nullable


class InputMessageTimestampAssigner : AssignerWithPunctuatedWatermarks<InputMessage> {
    override fun extractTimestamp(element: InputMessage, previousElementTimestamp: Long): Long {
        val zoneId = ZoneId.systemDefault()
        return element.sendAt
            .atZone(zoneId)
            .toEpochSecond() * 1000
    }

    @Nullable
    override fun checkAndGetNextWatermark(lastElement: InputMessage?, extractedTimestamp: Long): Watermark? {
        return Watermark(extractedTimestamp - 15)
    }
}
