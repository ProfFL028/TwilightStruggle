package me.proffl.ch02

import java.io.BufferedInputStream
import java.io.BufferedOutputStream
import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream
import java.io.RandomAccessFile
import java.nio.ByteBuffer

class BIOTransformer {
    fun transform(source: File, dest: File) {
        if (!dest.exists()) {
            dest.createNewFile()
        }

        val bis = BufferedInputStream(FileInputStream(source))
        val bos = BufferedOutputStream(FileOutputStream(dest))

        val bytes = ByteArray(1024 * 1024)
        var len = bis.read(bytes)
        while (len != -1) {
            bos.write(bytes, 0, len)
            len = bis.read(bytes)
        }

        bis.close()
        bos.close()
    }
}

class NIOTransformer {
    fun transform(source: File, dest: File) {
        if (!dest.exists())
            dest.createNewFile()

        val read = RandomAccessFile(source, "r").channel
        val write = RandomAccessFile(source, "rw").channel

        val buffer = ByteBuffer.allocate(1024 * 1024)
        var len = read.read(buffer)
        while (len > 0) {
            buffer.flip()
            write.write(buffer)
            buffer.clear()
            len = read.read(buffer)
        }

        write.close()
        read.close()
    }
}

fun main() {
    val source = File("D:\\Downloads\\CentOS-8.5.2111-x86_64-dvd1.iso")
    val dest1 = File("D:\\Downloads\\CentOS_bio.iso")
    val dest2 = File("D:\\Downloads\\CentOS_nio.iso")

    val bio = BIOTransformer()
    val nio = NIOTransformer()

    var start = System.currentTimeMillis()
    bio.transform(source, dest1)
    var end = System.currentTimeMillis()
    println("BIO: ${end - start}")

    start = System.currentTimeMillis()
    nio.transform(source, dest2)
    end = System.currentTimeMillis()
    println("NIO: ${end - start}")
}