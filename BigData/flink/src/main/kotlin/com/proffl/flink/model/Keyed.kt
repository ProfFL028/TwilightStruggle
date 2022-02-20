package com.proffl.flink.model

import org.apache.flink.api.java.functions.KeySelector
import org.slf4j.Logger
import org.slf4j.LoggerFactory

data class Keyed<IN, KEY, ID>(
    var wrapped: IN? = null,
    var key: KEY? = null,
    var id: ID? = null
)

class KeyedKeySelector<IN, KEY, ID>:KeySelector<Keyed<IN, KEY, ID>, KEY> {
    companion object {
        private val log:Logger = LoggerFactory.getLogger(KeyedKeySelector::class.java)
    }
    override fun getKey(value: Keyed<IN, KEY, ID>): KEY {
        log.info("I'm here: ---------------------------->${value.key}")
        return value.key!!
    }

}