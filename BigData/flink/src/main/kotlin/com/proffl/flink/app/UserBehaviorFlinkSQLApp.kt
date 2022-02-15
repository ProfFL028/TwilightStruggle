package com.proffl.flink.app

import com.proffl.flink.model.UserBehavior
import com.proffl.flink.model.UserBehaviorMap
import com.proffl.flink.model.UserBehaviorTimestampAssigner
import org.apache.flink.api.common.eventtime.WatermarkStrategy
import org.apache.flink.streaming.api.environment.StreamExecutionEnvironment
import org.apache.flink.table.api.DataTypes
import org.apache.flink.table.api.EnvironmentSettings
import org.apache.flink.table.api.Schema
import org.apache.flink.table.api.Slide
import org.apache.flink.table.api.bridge.java.StreamTableEnvironment
import org.apache.flink.types.Row
import java.time.Duration
import javax.xml.crypto.Data


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

    var envSetting = EnvironmentSettings.newInstance().inStreamingMode().build()
    var tableEnv = StreamTableEnvironment.create(env, envSetting)


    var dataTable = tableEnv.fromDataStream(dataStream,"itemId, behavior, timestamp.rowtime as ts")
    var windowAggTable = dataTable.filter("behavior='pv'")
        .window(Slide.over("1.hours").every("5.minutes").on("ts").`as`("w"))
        .groupBy("itemId, w")
        .select("itemId, w.end as windowEnd, itemId.count as cnt")

    var aggStream = tableEnv.toDataStream(windowAggTable, Row::class.java)
    tableEnv.createTemporaryView("data_table", dataStream, "itemId, behavior, timestamp.rowtime as ts")

    var resultTable = tableEnv.sqlQuery("""select * from (
        select *, row_number() over (partition by windowEnd order by cnt desc) as row_num from (
            select itemId, count(itemId) as cnt, HOP_END(ts, interval '5' minute, interval '1' hour) as windowEnd
                from data_table where behavior='pv'
            group by itemId, HOP(ts, interval '5' minute, interval '1' hour)
        )) where row_num <=5
    """.trimIndent())

    tableEnv.toRetractStream(resultTable, Row::class.java).print()

    env.execute()
}
