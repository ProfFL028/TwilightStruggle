package com.proffl.flink.model

import org.apache.flink.api.common.eventtime.SerializableTimestampAssigner
import org.apache.flink.api.common.functions.AggregateFunction
import org.apache.flink.api.common.functions.MapFunction
import org.apache.flink.api.common.state.ListState
import org.apache.flink.api.common.state.ListStateDescriptor
import org.apache.flink.api.java.functions.KeySelector
import org.apache.flink.configuration.Configuration
import org.apache.flink.streaming.api.functions.KeyedProcessFunction
import org.apache.flink.streaming.api.functions.windowing.WindowFunction
import org.apache.flink.streaming.api.windowing.windows.TimeWindow
import org.apache.flink.util.Collector
import java.sql.Timestamp
import kotlin.math.min

data class UserBehavior(
    var userId: Long = 0L,
    var itemId: Long = 0L,
    var categoryId: Int = 0,
    var behavior: String = "",
    var timestamp: Long = 0L
)

class UserBehaviorMap : MapFunction<String, UserBehavior> {
    override fun map(value: String?): UserBehavior {
        if (value != null) {
            var items = value.split(",")
            var userBehavior = UserBehavior()
            try {
                userBehavior.userId = items[0].trim().toLong()
                userBehavior.itemId = items[1].trim().toLong()
                userBehavior.categoryId = items[2].trim().toInt()
                userBehavior.behavior = items[3].trim()
                userBehavior.timestamp = items[4].trim().toLong()
            } catch (e: Exception) {
                println("parsing to UserBehavior error: $value")
            }
            return userBehavior
        }
        return UserBehavior()
    }
}

class UserBehaviorTimestampAssigner : SerializableTimestampAssigner<UserBehavior> {
    override fun extractTimestamp(element: UserBehavior, recordTimestamp: Long): Long {
        return element.timestamp * 1000
    }

}

class UserBehaviorKeySelector : KeySelector<UserBehavior, Long> {
    override fun getKey(value: UserBehavior): Long {
        return value.userId
    }

}

class UserBehaviorCountAgg : AggregateFunction<UserBehavior, Long, Long> {
    override fun createAccumulator(): Long {
        return 0
    }

    override fun add(value: UserBehavior, accumulator: Long): Long {
        return accumulator + 1
    }

    override fun getResult(accumulator: Long): Long {
        return accumulator
    }

    override fun merge(a: Long, b: Long): Long {
        return a + b
    }
}

class UserBehaviorWindowCountResult : WindowFunction<Long, ItemViewCount, Long, TimeWindow> {
    override fun apply(key: Long, window: TimeWindow, input: MutableIterable<Long>, out: Collector<ItemViewCount>) {
        out.collect(ItemViewCount(key, window.end, input.iterator().next()))
    }
}

data class ItemViewCount(
    var itemId: Long = 0L,
    var windowEnd: Long = 0L,
    var count: Long = 0L
)

class ItemViewCountKeySelector : KeySelector<ItemViewCount, Long> {
    override fun getKey(value: ItemViewCount): Long {
        return value.windowEnd
    }
}

class ItemTopN(private val threshold: Int = 3) : KeyedProcessFunction<Long, ItemViewCount, String>() {
    private lateinit var itemState: ListState<ItemViewCount>

    override fun open(parameters: Configuration?) {
        super.open(parameters)
        itemState = runtimeContext.getListState(ListStateDescriptor("item-state", ItemViewCount::class.java))
    }

    override fun processElement(value: ItemViewCount, ctx: Context, out: Collector<String>) {
        itemState.add(value)
        ctx.timerService().registerEventTimeTimer(value.windowEnd + 100L)
    }

    override fun onTimer(timestamp: Long, ctx: OnTimerContext, out: Collector<String>) {
        super.onTimer(timestamp, ctx, out)

        var itemViewCounts = itemState.get()
        var list = ArrayList<ItemViewCount>()
        for (itemViewCount in itemViewCounts) {
            list.add(itemViewCount)
        }
        list.sortWith { o1, o2 -> o1.count.toInt() - o2.count.toInt() }
        var sb = StringBuilder()
        sb.append("-----------------\n").append("time:${Timestamp(timestamp - 100L)}\n")
        for (i in 0 until min(list.size, threshold)) {
            sb.append("No.${i + 1}: count( ${list[i].itemId} )=${list[i].count}\n")
        }
        sb.append("------------------")
        Thread.sleep(1000)
        out.collect(sb.toString())
    }

}
