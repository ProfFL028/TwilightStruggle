package com.proffl.flink.model

data class Alert<Event, Value>(
    var ruleId: Integer = Integer(0),
    var violatedRule: Rule? = null,
    var key: String = "",
    var triggeringEvent: Event? = null,
    var triggeringValue: Value? = null
) {

}