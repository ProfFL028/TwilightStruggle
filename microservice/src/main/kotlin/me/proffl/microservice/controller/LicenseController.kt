package me.proffl.microservice.controller

import me.proffl.microservice.model.License
import me.proffl.microservice.service.LicenseService
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.*

@RestController
@RequestMapping(value = ["v1/organization/{organizationId}/license"])
class LicenseController(@Autowired var licenseService: LicenseService) {

    @GetMapping(value = ["/{licenseId}"])
    fun getLicense(
        @PathVariable("organizationId") organizationId: String,
        @PathVariable("licenseId") licenseId: String
    ): ResponseEntity<License> {
        val license = licenseService.getLicense(licenseId, organizationId)
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
        @RequestBody request: License
    ): ResponseEntity<String> {
        return ResponseEntity.ok(licenseService.createLicense(request, organizationId))
    }

    @DeleteMapping(value = ["/{licenseId}"])
    fun createLicense(
        @PathVariable("organizationId") organizationId: String,
        @PathVariable("licenseId") licenseId: String
    ): ResponseEntity<String> {
        return ResponseEntity.ok(licenseService.deleteLicense(licenseId, organizationId))
    }
}