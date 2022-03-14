package me.proffl.core

import me.proffl.entity.Report
import java.io.FileReader

class TemplateReader() {
    companion object {
        fun read(filename: String): Report {
            val fileReader = FileReader(filename)

            val report = TemplateParser.parse(fileReader.readLines())
            fileReader.close()
            return report
        }
    }
}