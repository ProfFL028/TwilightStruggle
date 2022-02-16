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
import org.apache.flink.util.Preconditions
import java.util.SplittableRandom

abstract class BaseGenerator<T>(
    var maxRecordsPerSecond: Int = -1
): RichParallelSourceFunction<T>(), CheckpointedFunction {
    companion object {
        private const val serialVersionUID = 1L
    }

    init {
        Preconditions.checkArgument(maxRecordsPerSecond == -1 || maxRecordsPerSecond > 0,
            "maxRecordsPerSecond should be -1(infinite) or > 0")
    }

    override fun open(parameters: Configuration?) {
        super.open(parameters)
        if (id == -1L) {
            id = runtimeContext.indexOfThisSubtask.toLong()
        }
    }

    override fun run(ctx: SourceFunction.SourceContext<T>) {
        val numberOfParallelSubtasks = runtimeContext.numberOfParallelSubtasks
        val throttle = Throttle(maxRecordsPerSecond, numberOfParallelSubtasks)
        val rnd = SplittableRandom()

        val obj = ctx.checkpointLock

        while (running) {
            val event = randomEvent(rnd, id)

            synchronized(obj) {
                if (event != null) {
                    ctx.collect(event)
                }
                id += numberOfParallelSubtasks
            }

            throttle.throttle()
        }
    }

    override fun cancel() {
        this.running = false
    }

    override fun snapshotState(context: FunctionSnapshotContext?) {
        idState.clear()
        idState.add(id)
    }

    override fun initializeState(context: FunctionInitializationContext) {
        idState = context.operatorStateStore.getUnionListState(ListStateDescriptor("ids", BasicTypeInfo.LONG_TYPE_INFO))
    }

    abstract fun randomEvent(rnd: SplittableRandom, id: Long): T

    @Volatile private var running: Boolean = false
    private var id: Long = -1
    @Transient private lateinit var idState: ListState<Long>
}