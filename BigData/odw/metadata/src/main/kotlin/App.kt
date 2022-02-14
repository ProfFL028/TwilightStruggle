import com.proffl.entity.CodeTable
import com.proffl.entity.poi.PoiRowToEntity
import org.apache.poi.hssf.usermodel.HSSFWorkbook
import java.io.File
import java.io.FileInputStream

fun main(args: Array<String>) {
    var metaExcelPath = "/Users/proffl/TwilightStruggle/BigData/odw/metadata/src/main/resources/数据标准化－码表.xls"
    var metaWorkbook = HSSFWorkbook(FileInputStream(File(metaExcelPath)))

    var i = 10
    for (sheet in metaWorkbook.sheetIterator()) {
        for (row in sheet.rowIterator()) {
            var codeTable = PoiRowToEntity.rowToEntity(row, CodeTable::class.java)
            println(codeTable)
        }
        i--
        if (i > 0) {
            break
        }
    }

}