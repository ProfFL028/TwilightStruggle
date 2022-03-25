package me.proffl.app.example

import me.proffl.core.ReportFileReader

fun main() {
    val report = ReportFileReader().read("report/src/main/resources/template.report")
    println(report)


}