package com.proffl.app

import com.proffl.job.CodeTableJob

fun main(args: Array<String>) {
    var codeTablePath = "/Users/proffl/TwilightStruggle/BigData/odw/metadata/src/main/resources/数据标准化－码表.xls"
    var codeTableJob = CodeTableJob()
    codeTableJob.addProperties(CodeTableJob.CODE_TABLE_PATH, codeTablePath)
    codeTableJob.work()
}
