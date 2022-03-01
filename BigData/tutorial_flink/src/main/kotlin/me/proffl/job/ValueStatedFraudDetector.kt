package me.proffl.job

import me.proffl.entity.Alert
import me.proffl.entity.Transaction
import org.apache.flink.api.common.state.ValueState
import org.apache.flink.api.common.state.ValueStateDescriptor
import org.apache.flink.api.common.typeinfo.TypeInformation
import org.apache.flink.configuration.Configuration
import org.apache.flink.streaming.api.functions.KeyedProcessFunction
import org.apache.flink.util.Collector

class ValueStatedFraudDetector : KeyedProcessFunction<Long, Transaction, Alert>() {

    @Transient
    private lateinit var flagState: ValueState<Boolean?>

    @Transient
    private lateinit var timerState: ValueState<Long?>

    override fun open(parameters: Configuration) {
        super.open(parameters)
        val flagDescriptor = ValueStateDescriptor("flag-state", TypeInformation.of(Boolean::class.java))
        flagState = runtimeContext.getState(flagDescriptor)
        val timerDescriptor = ValueStateDescriptor("timer-state", TypeInformation.of(Long::class.java))
        timerState = runtimeContext.getState(timerDescriptor)
    }

    override fun processElement(value: Transaction, ctx: Context, out: Collector<Alert>) {
        val lastTransactionWasSmall = flagState.value()
        if (lastTransactionWasSmall != null) {
            if (value.amount > 500.0) {
                out.collect(Alert(value.accountId))
            }
            cleanUp(ctx)
        }

        if (value.amount <= 1.0) {
            flagState.update(true)
            val timer = ctx.timerService().currentProcessingTime() + 1 * 60 * 1000L
            ctx.timerService().registerEventTimeTimer(timer)
            timerState.update(timer)
        }
    }

    override fun onTimer(timestamp: Long, ctx: OnTimerContext?, out: Collector<Alert>?) {
        timerState.clear()
        flagState.clear()
    }

    private fun cleanUp(ctx: Context) {
        val timer = timerState.value()
        if (timer != null) {
            ctx.timerService().deleteProcessingTimeTimer(timer)
        }

        timerState.clear()
        flagState.clear()
    }
}