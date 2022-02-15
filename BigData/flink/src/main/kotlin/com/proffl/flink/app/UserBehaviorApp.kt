package com.proffl.flink.app

import com.proffl.flink.model.*
import org.apache.flink.api.common.eventtime.WatermarkStrategy
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import org.apache.flink.streaming.api.windowing.assigners.SlidingEventTimeWindows
import org.apache.flink.streaming.api.windowing.time.Time
import java.time.Duration


fun main() {
    var env = StreamExecutionEnvironment.getExecutionEnvironment()
    env.parallelism = 1

    var dataStream = env.readTextFile("E:\\TwilightStruggle\\BigData\\flink\\src\\main\\resources\\user_behavior.csv")
        .map(UserBehaviorMap())
        .filter { value -> value.behavior == "pv" }
        .assignTimestampsAndWatermarks(
            WatermarkStrategy
                .forBoundedOutOfOrderness<UserBehavior?>(Duration.ofSeconds(60))
                .withTimestampAssigner(
                    UserBehaviorTimestampAssigner()
                )
        )

    var aggStream = dataStream.keyBy(UserBehaviorKeySelector())
        .window(SlidingEventTimeWindows.of(Time.hours(1), Time.minutes(5)))
        .aggregate(UserBehaviorCountAgg(), UserBehaviorWindowCountResult())

    var topNStream = aggStream.keyBy(ItemViewCountKeySelector()).process(ItemTopN(5))

    topNStream.print()

    env.execute()
}
