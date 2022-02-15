package com.proffl.entity.poi

import java.lang.annotation.Documented


@Documented
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.RUNTIME)
annotation class XlsxSheet(val value: String)

@Documented
@Target(AnnotationTarget.FIELD)
@Retention(AnnotationRetention.RUNTIME)
annotation class XlsxField(val columnIndex: Int)

@Documented
@Target(AnnotationTarget.CLASS, AnnotationTarget.FIELD)
@Retention(AnnotationRetention.RUNTIME)
annotation class XlsxCompositeField(val from: Int, val to: Int, val rel:Boolean=false)