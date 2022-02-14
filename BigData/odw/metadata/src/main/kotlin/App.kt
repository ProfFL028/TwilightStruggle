import org.apache.poi.hssf.usermodel.HSSFWorkbook
import java.io.File
import java.io.FileInputStream

fun main() {
    var metaExcelPath = "/Users/proffl/TwilightStruggle/BigData/odw/metadata/src/main/resources/数据标准化－码表.xls"
    var metaWorkbook = HSSFWorkbook(FileInputStream(File(metaExcelPath)))

    for (sheet in metaWorkbook.sheetIterator()) {
        println(sheet.sheetName)

    }
}