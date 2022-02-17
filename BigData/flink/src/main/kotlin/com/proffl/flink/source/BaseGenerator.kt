package com.proffl.flink.source

import org.apache.flink.api.common.state.ListState
import org.apache.flink.api.common.state.ListStateDescriptor
import org.apache.flink.api.common.typeinfo.BasicTypeInfo
import org.apache.flink.configuration.Configuration
import org.apache.flink.runtime.state.FunctionInitializationContext
import org.apache.flink.runtime.state.FunctionSnapshotContext
import org.apache.flink.streaming.api.checkpoint.CheckpointedFunction
import org.apache.flink.streaming.api.functions.source.RichParallelSourceFunction
import org.apache.flink.streaming.api.functions.source.SourceFunction
import java.util.*

abstract class BaseGenerator<T>(var maxRecordsPerSecond: Int=-1) : RichParallelSourceFunction<T>(), CheckpointedFunction {
    override fun run(ctx: SourceFunction.SourceContext<T>) {
        val tasks = runtimeContext.numberOfParallelSubtasks
        val throttle = Throttle(maxRecordsPerSecond, tasks)
        val rnd = SplittableRandom()

        var obj = ctx.checkpointLock

        while (running) {
            id += tasks
            synchronized(obj) {
                ctx.collect(randomEvent(rnd, id))
            }
            throttle.throttle()
        }
    }

    abstract fun randomEvent(rnd: SplittableRandom, id: Long): T

    override fun cancel() {
        running = false
    }

    override fun open(parameters: Configuration?) {
        super.open(parameters)
        if (id == -1L) {
            id = runtimeContext.indexOfThisSubtask.toLong()
        }
    }

    override fun initializeState(context: FunctionInitializationContext) {
        idState = context.operatorStateStore.getUnionListState(ListStateDescriptor("idState", BasicTypeInfo.LONG_TYPE_INFO))
    }

    override fun snapshotState(context: FunctionSnapshotContext?) {
        idState.clear()
        idState.add(id)
    }

    private var id = -1L
    private lateinit var idState: ListState<Long>
    private var running = true
}
