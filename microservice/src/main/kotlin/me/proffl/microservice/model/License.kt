package me.proffl.microservice.model

data class License(
    var id: Int = 0,
    var licenseId: String = "",
    var organizationId: String = "",
    var description: String = "",
    var productName: String = "",
    var licenseType: String = ""
) {
}