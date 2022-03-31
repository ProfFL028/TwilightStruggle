package me.proffl.app

import org.apache.http.client.methods.HttpGet
import org.apache.http.impl.client.HttpClients
import org.apache.http.util.EntityUtils

fun main() {
    val client = HttpClients.createDefault()
    val httpGet = HttpGet("https://codeforces.com/contest/1658/problems")
    val response = client.execute(httpGet)
    val questions = EntityUtils.toString(response.entity, "UTF-8")
}