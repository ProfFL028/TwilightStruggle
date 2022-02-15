package com.proffl.job

import com.github.junrar.Junrar
import java.io.File

class RarExtractJob: Job() {
    companion object {
        const val FILE_PATH= "filePath"
        const val DEST_DIR = "destDir"
        const val DEFAULT_DEST_DIR = "/tmp/doc/"
    }
    override fun work() {
        if (properties.keys.contains(FILE_PATH)) {
            var filePath = properties.getValue(FILE_PATH).toString()
            var destDir = properties.getOrDefault(DEST_DIR, DEFAULT_DEST_DIR).toString()
            if (!destDir.endsWith("/")) {
                destDir += "/"
            }
            var destPath = File(destDir)
            if (!destPath.exists()) {
                destPath.mkdirs()
            }
            Junrar.extract(filePath, destDir)
        }
    }
}