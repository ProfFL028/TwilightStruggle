package me.proffl.microservice.service

import me.proffl.microservice.model.License
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.context.MessageSource
import org.springframework.stereotype.Service
import java.util.*

@Service
class LicenseService(
    @Autowired val messageSource: MessageSource
) {
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

    fun createLicense(license: License?, organizationId: String, locale: Locale): String {
        var responseMessage = ""
        if (license != null) {
            license.organizationId = organizationId
            responseMessage =
                String.format(messageSource.getMessage("license.creat.message", null, locale), license.toString())
        }
        return responseMessage
    }

    fun updateLicense(license: License?, organizationId: String): String {
        var responseMessage = ""
        if (license != null) {
            license.organizationId = organizationId
            responseMessage = String.format(
                messageSource.getMessage("license.update.message", null, Locale.CHINA),
                license.toString()
            )
        }
        return responseMessage
    }

    fun deleteLicense(licenseId: String, organizationId: String): String {
        return "Deleting license with id $licenseId for the organization $organizationId"
    }
}