package com.proffl.flink.model

import com.fasterxml.jackson.annotation.JsonProperty
import java.time.LocalDateTime
import java.util.*


class Backup(@JsonProperty var inputMessages: List<InputMessage>? = null,
             @JsonProperty var backupTimestamp: LocalDateTime? = null,
             @JsonProperty var uuid: UUID? = null) {


    constructor(inputMessages: List<InputMessage>?, backupTimestamp: LocalDateTime?) : this() {
        this.inputMessages = inputMessages
        this.backupTimestamp = backupTimestamp
        uuid = UUID.randomUUID()
    }

}
