package me.proffl.microservice.controller

import me.proffl.microservice.model.License
import me.proffl.microservice.service.LicenseService
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.linkTo
import org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.methodOn
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.*
import java.util.*

@RestController
@RequestMapping(value = ["v1/organization/{organizationId}/license"])
class LicenseController(
    @Autowired var licenseService: LicenseService,
) {
    @GetMapping(value = ["/{licenseId}"])
    fun getLicense(
        @PathVariable("organizationId") organizationId: String,
        @PathVariable("licenseId") licenseId: String
    ): ResponseEntity<License> {
        val license = licenseService.getLicense(licenseId, organizationId)
        license.add(
            linkTo(methodOn(LicenseController::class.java).getLicense(organizationId, license.licenseId)).withSelfRel(),
            linkTo(methodOn(LicenseController::class.java).createLicense(organizationId, license, Locale.US)).withRel("createLicense"),
            linkTo(methodOn(LicenseController::class.java).updateLicense(organizationId, license)).withRel("updateLicense"),
            linkTo(methodOn(LicenseController::class.java).deleteLicense(organizationId, license.licenseId)).withRel("deleteLicense")
        )
        return ResponseEntity.ok(license)
    }

    @PutMapping
    fun updateLicense(
        @PathVariable("organizationId") organizationId: String,
        @RequestBody request: License
    ): ResponseEntity<String> {
        return ResponseEntity.ok(licenseService.updateLicense(request, organizationId))
    }

    @PostMapping
    fun createLicense(
        @PathVariable("organizationId") organizationId: String,
        @RequestBody request: License,
        @RequestHeader(value = "Accept-Language", required = false) locale: Locale
    ): ResponseEntity<String> {
        return ResponseEntity.ok(licenseService.createLicense(request, organizationId, locale))
    }

    @DeleteMapping(value = ["/{licenseId}"])
    fun deleteLicense(
        @PathVariable("organizationId") organizationId: String,
        @PathVariable("licenseId") licenseId: String
    ): ResponseEntity<String> {
        return ResponseEntity.ok(licenseService.deleteLicense(licenseId, organizationId))
    }
}