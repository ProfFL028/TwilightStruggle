package me.proffl.worker

import org.slf4j.LoggerFactory
import java.nio.ByteBuffer
import java.nio.channels.SelectableChannel

class EchoWork: ChannelReader() {
    companion object {
        private val logger = LoggerFactory.getLogger(EchoWork::class.java)
    }
    override fun handle(byteBuffer: ByteBuffer, bufferSize: Int) {
        logger.info(byteBuffer.toString())
    }


}
