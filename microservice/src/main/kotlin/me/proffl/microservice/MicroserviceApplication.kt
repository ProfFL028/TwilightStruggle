package me.proffl.microservice

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication
import org.springframework.context.annotation.Bean
import org.springframework.context.support.ResourceBundleMessageSource
import org.springframework.web.servlet.LocaleResolver
import org.springframework.web.servlet.i18n.SessionLocaleResolver
import java.util.*

@SpringBootApplication
class MicroserviceApplication {
    @Bean fun localResolver(): LocaleResolver {
        val localResolver = SessionLocaleResolver()
        localResolver.setDefaultLocale(Locale.US)
        return localResolver
    }

    @Bean fun messageSource(): ResourceBundleMessageSource {
        val messageSource = ResourceBundleMessageSource()
        // doesn't throw an error if a message isn't found, instead it returns the message code.
        messageSource.setUseCodeAsDefaultMessage(true)
        messageSource.setBasename("messages")
        return messageSource
    }
}

fun main(args: Array<String>) {
    runApplication<MicroserviceApplication>(*args)
}
