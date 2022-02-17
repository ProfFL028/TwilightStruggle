package com.proffl.flink.config

class Config(
    inputParams: Parameters,
    stringParams: List<Param<String>>,
    intParams: List<Param<Integer>>,
    boolParams: List<Param<Boolean>>
) {
    private val values: MutableMap<Param<*>, Any> = HashMap()

    fun <T> put(key: Param<T>, value: T) {
        values[key] = value!!
    }

    fun <T> get(key: Param<T>): T {
        return key.type.cast(values[key])
    }

    init {
        overrideDefaults(inputParams, stringParams)
        overrideDefaults(inputParams, intParams)
        overrideDefaults(inputParams, boolParams)
    }

    private fun <T> overrideDefaults(inputParams: Parameters, params: List<Param<T>>) {
        for (param in params) {
            this.put(param, inputParams.getOrDefault(param))
        }
    }

    companion object {
        fun fromParameters(parameters: Parameters):Config {
            return Config(parameters, Parameters.STRING_PARAMS, Parameters.INT_PARAMS, Parameters.BOOL_PARAMS)
        }
    }
}