package me.proffl.app.example

import java.io.File
import java.io.FileReader

class ReadExcelExample {
}

fun main() {
    val report = FileReader(File("template.report"))
    val data = report.readLines()
}