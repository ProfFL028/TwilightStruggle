package com.proffl.app

import com.proffl.job.RarExtractJob


fun main() {
    var rarExtractJob = RarExtractJob()
    rarExtractJob.addProperties(RarExtractJob.FILE_PATH, "/Users/proffl/TwilightStruggle/BigData/odw/metadata/src/main/resources/标准化文档-20220112.rar")
    rarExtractJob.addProperties(RarExtractJob.DEST_DIR, "/tmp/doc/")

    rarExtractJob.work()
}