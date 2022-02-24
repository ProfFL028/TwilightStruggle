import java.io.InputStream
import java.util.concurrent.ThreadLocalRandom

class MyIntStream(
    var rand: ThreadLocalRandom,
    var min: Int = 0,
    var max: Int = 100000
) : InputStream() {

    override fun read(): Int {
        return rand.nextInt(min,max)
    }
}