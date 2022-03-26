package me.proffl.app.example

import org.hibernate.cfg.Configuration
import org.hibernate.transform.AliasToEntityMapResultTransformer

fun main() {
    val sessionFactory = Configuration().configure().buildSessionFactory()
    val session = sessionFactory.openSession()

    session.use {
        val transaction = session.beginTransaction()
        val query = session.createNativeQuery("select * from frm_user")
        // though it is deprecated, there's no alternative for it unless you upgrade to hibernate6
        query.setResultTransformer(AliasToEntityMapResultTransformer.INSTANCE)
        val result = query.list() as List<Map<String, Object>>

        for (row in result) {
            for (key in row.keys) {
                println("$key -> ${row[key]}")
            }
        }

        transaction.commit()

    }
}