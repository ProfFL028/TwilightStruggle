package me.proffl.microservice.config

import org.springframework.context.annotation.Configuration
import org.springframework.security.config.annotation.web.builders.HttpSecurity
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter

@Configuration
@EnableWebSecurity
class SecurityConfig : WebSecurityConfigurerAdapter() {

    override fun configure(http: HttpSecurity) {
        // super.configure(http)
        // inorder to making permitAll work, we need to comment super.configure(http) for it already configured anyRequest before.
        http.cors().and().csrf().disable().authorizeRequests()
            .anyRequest().permitAll()
    }
}