package me.proffl.ch02

import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.AsynchronousChannelGroup
import java.nio.channels.AsynchronousServerSocketChannel
import java.nio.channels.AsynchronousSocketChannel
import java.nio.channels.CompletionHandler
import java.util.*
import java.util.concurrent.ExecutionException
import java.util.concurrent.Executors


class AIOServer(var port: Int) {
    private val executorService = Executors.newCachedThreadPool()
    private val threadGroup = AsynchronousChannelGroup.withCachedThreadPool(executorService, 1)
    val assc = AsynchronousServerSocketChannel.open(threadGroup)

    fun start() {
        assc.bind(InetSocketAddress(port))
        println("server started")
        assc.accept(this, ServerCompletionHandler())
        Thread.sleep(Long.MAX_VALUE)
    }
}

class ServerCompletionHandler : CompletionHandler<AsynchronousSocketChannel, AIOServer> {

    override fun completed(result: AsynchronousSocketChannel, attachment: AIOServer) {
        attachment.assc.accept(attachment, this)
        read(result)
    }

    override fun failed(exc: Throwable, attachment: AIOServer) {
        exc.printStackTrace()
    }

    private fun read(asc: AsynchronousSocketChannel) {
        val buffer = ByteBuffer.allocate(1024)
        asc.read(buffer, buffer, object : CompletionHandler<Int, ByteBuffer> {
            override fun completed(resultSize: Int, attachment: ByteBuffer) {
                attachment.flip() //进行读取之后,重置标识位
                println("Server端收到客户端的数据长度为:$resultSize") //获得读取的字节数
                val resultData = String(attachment.array()).trim { it <= ' ' } //获取读取的数据
                println("Server端收到客户端的数据信息为:$resultData")
                val response = "From服务端To客户端: 于" + Date() + "收到了请求数据" + resultData
                write(asc, response)
            }

            override fun failed(exc: Throwable, attachment: ByteBuffer) {
                exc.printStackTrace()
            }
        })
    }

    private fun write(asc: AsynchronousSocketChannel, response: String) {
        try {
            val buf = ByteBuffer.allocate(1024)
            buf.put(response.toByteArray())
            buf.flip()
            val future = asc.write(buf)
            future.get()
        } catch (e: InterruptedException) {
            e.printStackTrace()
        } catch (e: ExecutionException) {
            e.printStackTrace()
        }
    }

}

fun main() {
    val server = AIOServer(8765)
    server.start()
}