package me.proffl.reg.example

import java.util.regex.Pattern

/**
 * input   <n1=v1 n2=v2 n3=v3> n1=v1 n2=v2 n3=v3 <v1=pq v2=ds> v1=pq v2=ds
 * output  <v1=n1 v2=n2 v3=n3> n1=v1 n2=v2 n3=v3 <pq=v1 ds=v2> v1=pq v2=ds
 */
fun main() {
    val pattern = Pattern.compile("<[^>]+>")
    val pairPattern = Pattern.compile("(\\w+)=(\\w+)")
    val input = "<n1=v1 n2=v2 n3=v3> n1=v1 n2=v2 n3=v3 <v1=pq v2=ds> v1=pq v2=ds"

    val sbuf = StringBuilder()
    val enclosePair =pattern.matcher(input)
    while (enclosePair.find()) {
        val pairMatcher = pairPattern.matcher(enclosePair.group())
        enclosePair.appendReplacement(sbuf, pairMatcher.replaceAll("$2=$1"))
    }
    enclosePair.appendTail(sbuf)
    println(sbuf.toString())
}