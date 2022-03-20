package me.proffl.microservice.service

import me.proffl.microservice.model.License
import org.springframework.stereotype.Service
import java.util.*

@Service
class LicenseService {
    fun getLicense(licenseId: String, organizationId: String): License {
        val license = License()
        license.id = Random().nextInt(1000)
        license.licenseId = licenseId
        license.organizationId = organizationId
        license.description = "Software product"
        license.productName = "Ostock"
        license.licenseType = "full"

        return license
    }

    fun createLicense(license: License?, organizationId: String):String {
        var responseMessage = ""
        if (license != null) {
            license.organizationId = organizationId
            responseMessage = "This is the post and the object is $license"
        }
        return responseMessage
    }
    
    fun updateLicense(license: License?, organizationId: String): String {
        var responseMessage = ""
        if (license != null) {
            license.organizationId = organizationId
            responseMessage = "This is the put and the object is $license"
        }
        return responseMessage
    }

    fun deleteLicense(licenseId: String, organizationId: String): String {
        return "Deleting license with id $licenseId for the organization $organizationId"
    }
}