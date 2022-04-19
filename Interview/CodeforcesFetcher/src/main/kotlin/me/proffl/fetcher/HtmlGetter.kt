package me.proffl.fetcher

import org.apache.http.client.HttpClient
import org.apache.http.client.methods.HttpGet
import org.apache.http.impl.client.HttpClients
import org.apache.http.util.EntityUtils
import org.jsoup.Jsoup
import org.jsoup.nodes.Document

class HtmlGetter {

    fun get(url: String): Document? {
        val httpClient = HttpClients.createDefault()
        val httpGet = HttpGet(url)
        val response = httpClient.execute(httpGet)
        if (response.statusLine.statusCode == 200) {
            val html = EntityUtils.toString(response.entity)
            return Jsoup.parse(html)
        } else {
            return null
        }
    }
}