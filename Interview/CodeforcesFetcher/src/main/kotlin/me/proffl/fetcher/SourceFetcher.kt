package me.proffl.fetcher

class SourceFetcher {
    fun fetch(url: String): String {
        if (url.isEmpty()) {
            println("$url is empty!!")
            return ""
        }
        val document = HtmlGetter().get(url) ?: return ""
        println("get document success")

        val codeLines = document.select("ol.linenums li")
        val codeBuilder = StringBuilder()
        for (code in codeLines) {
            codeBuilder.append(code.html())
        }
        println("generate code success")
        return codeBuilder.toString()
    }
}