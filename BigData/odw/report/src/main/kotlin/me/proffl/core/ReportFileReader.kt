package me.proffl.core

import me.proffl.entity.Report
import java.io.FileReader

class ReportFileReader {
        fun read(filename: String): Report {
            val fileReader = FileReader(filename)

            val report = ReportParser().parse(fileReader.readLines())
            fileReader.close()
            return report
        }
}