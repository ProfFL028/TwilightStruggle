import org.apache.http.client.methods.HttpGet
import org.apache.http.impl.client.HttpClients
import org.apache.http.util.EntityUtils
import org.jsoup.Jsoup

fun main() {
    val problemLinkPattern = Regex("<a href=\"/contest/(\\d+)/problem/(\\w+)\"> (\\w+) - ([^<]+)</a>")

    val contestId = 1671
    val questionId = 'F'
    val client = HttpClients.createDefault()
    var pageId = 1
    var foundCount = 0
    while (true) {
        val url = "https://codeforces.com/contest/$contestId/status/page/$pageId?order=BY_JUDGED_DESC"
        val statusGet = HttpGet(url)
        val response = client.execute(statusGet)
        if (response.statusLine.statusCode == 200) {
            val content = EntityUtils.toString(response.entity)
            val document = Jsoup.parse(content)
            val tables = document.select("table.status-frame-datatable")
            for (table in tables) {
                val trs = table.getElementsByAttribute("data-submission-id")
                for (tr in trs) {
                    if (tr.select("td span.verdict-accepted").count() == 1) {
                        val hrefInTd = tr.select("td[data-problemid] a")
                        val hrefFinder = problemLinkPattern.find(hrefInTd.toString())
                        val question = hrefFinder!!.groupValues[2]
                        if (question[0] == questionId) {
                            val submitHref = tr.select("td.id-cell a")
                            println("https://codeforces.com${submitHref.attr("href")}")
                            foundCount++
                            if (foundCount >= 3)
                                return
                        }
                    }
                }
            }
        } else {
            println("cannot access page: $url")
            return
        }
        pageId++
        println("continue searching solutions in $pageId")
    }
}