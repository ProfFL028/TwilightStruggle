package me.proffl.util

/**
 * It's just a simply wrap of try-finally statement, but nothing to do with resource.close() function.
 * That's why java add `with` statement with resource.
 * We can use `use` function in AutoClosable now.
 */
inline fun <T : AutoCloseable, R> autoTry(resource: T, block: (T) -> R): R {
    try {
        return block(resource)
    } finally {
        resource.close()
    }
}