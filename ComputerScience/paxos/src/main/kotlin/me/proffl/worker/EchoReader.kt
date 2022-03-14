package me.proffl.worker

import org.slf4j.LoggerFactory
import java.nio.ByteBuffer

class EchoReader : ChannelReader() {
    companion object {
        private val logger = LoggerFactory.getLogger(EchoReader::class.java)
    }

    override fun handle(byteBuffer: ByteBuffer, bufferSize: Int) {
        logger.info(String(byteBuffer.array()).substring(bufferSize))
    }


}
