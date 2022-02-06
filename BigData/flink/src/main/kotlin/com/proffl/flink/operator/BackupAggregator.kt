package com.proffl.flink.operator

import com.proffl.flink.model.Backup
import com.proffl.flink.model.InputMessage
import org.apache.flink.api.common.functions.AggregateFunction
import java.time.LocalDateTime

class BackupAggregator: AggregateFunction<InputMessage, MutableList<InputMessage>, Backup> {
    override fun createAccumulator(): MutableList<InputMessage> {
        return ArrayList()
    }

    override fun add(value: InputMessage, accumulator: MutableList<InputMessage>): MutableList<InputMessage> {
        accumulator.add(value)
        return accumulator
    }

    override fun getResult(accumulator: MutableList<InputMessage>?): Backup {
        var backup = Backup(accumulator, LocalDateTime.now())
        return backup
    }

    override fun merge(a: MutableList<InputMessage>, b: MutableList<InputMessage>): MutableList<InputMessage> {
        a.addAll(b)
        return a
    }
}
