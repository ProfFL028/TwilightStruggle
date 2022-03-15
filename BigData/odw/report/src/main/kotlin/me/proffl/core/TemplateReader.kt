package me.proffl.core

import me.proffl.entity.Report
import java.io.FileReader

class TemplateReader() {
    companion object {
        fun read(filename: String): Report {
            val fileReader = FileReader(filename)

            val report = TemplateParser(fileReader.readLines()).parse()
            fileReader.close()
            return report
        }
    }
}