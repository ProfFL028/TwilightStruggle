package me.proffl.processor

import org.apache.kafka.streams.processor.api.Processor
import org.apache.kafka.streams.processor.api.ProcessorContext
import org.apache.kafka.streams.processor.api.Record

class SayHelloProcessor(): Processor<Void, String, Void, Void> {
    override fun init(context: ProcessorContext<Void, Void>) {

    }

    override fun process(record: Record<Void, String>) {
        println("(Processor API)Hello, ${record.value()}")
    }

    override fun close() {
    }
}
