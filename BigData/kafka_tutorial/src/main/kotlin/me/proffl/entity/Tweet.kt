package me.proffl.entity

import com.google.gson.annotations.SerializedName

data class Tweet(
    @SerializedName("CreatedAt")
    var createdAt: Long = 0L,
    @SerializedName("Id")
    var id: Long = 0L,
    @SerializedName("Lang")
    var lang: String = "",
    @SerializedName("Retweet")
    var retweet: Boolean = false,
    @SerializedName("Text")
    var text: String = ""
) {
}

class DummyTranslate {
    fun translate(tweet: Tweet?): Tweet {
        if (tweet == null) {
            return Tweet()
        }
        val translatedTweet = Tweet()
        translatedTweet.id = tweet.id
        translatedTweet.createdAt = tweet.createdAt
        translatedTweet.lang = "en"
        translatedTweet.retweet = tweet.retweet
        translatedTweet.text = "Translated-----${tweet.text}---"

        return translatedTweet
    }
}
