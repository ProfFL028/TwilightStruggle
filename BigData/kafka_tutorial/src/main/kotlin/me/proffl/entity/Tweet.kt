package me.proffl.entity

import com.google.gson.annotations.SerializedName

data class Tweet(
    @SerializedName("CreatedAt")
    var createdAt: Long,
    @SerializedName("Id")
    var id: Long,
    @SerializedName("Lang")
    var lang: String,
    @SerializedName("Retweet")
    var retweet: Boolean,
    @SerializedName("Text")
    var text: String
) {
}
