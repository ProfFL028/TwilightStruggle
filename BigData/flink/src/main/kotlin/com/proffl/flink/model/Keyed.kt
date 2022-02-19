package com.proffl.flink.model

import com.esotericsoftware.kryo.util.IntMap.Keys
import org.apache.flink.api.java.functions.KeySelector

data class Keyed<IN, KEY, ID>(
    var wrapped: IN,
    var key: KEY,
    var id: ID
)

class KeyedKeySelector<IN, KEY, ID>:KeySelector<Keyed<IN, KEY, ID>, KEY> {
    override fun getKey(value: Keyed<IN, KEY, ID>): KEY {
        return value.key
    }

}