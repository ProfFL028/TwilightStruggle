package com.proffl.flink.model

import org.apache.flink.shaded.jackson2.com.fasterxml.jackson.databind.annotation.JsonSerialize
import java.time.LocalDateTime
import java.util.*

@JsonSerialize
class InputMessage(var sender: String, var recipient: String, var sendAt: LocalDateTime, var message: String) {

    override fun equals(o: Any?): Boolean {
        if (this === o) return true
        if (o == null || javaClass != o.javaClass) return false
        val message1 = o as InputMessage
        return sender == o.sender && recipient == o.recipient && sendAt == o.sendAt && message == o.message
    }
}
