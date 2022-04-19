package me.proffl.app

import me.proffl.fetcher.SourceFetcher


fun main() {
    val sourceFetcher = SourceFetcher()
    println(sourceFetcher.fetch("https://codeforces.com/contest/1659/submission/154047740"))
}