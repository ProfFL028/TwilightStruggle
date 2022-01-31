import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.io.SequenceFile;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.util.ReflectionUtils;

import java.io.IOException;
import java.net.URI;

public class SequenceFileReader {
    public static void main(String[] args) throws IOException {
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(args[0]), conf);
        Path path = new Path(args[0]);

        SequenceFile.Reader reader = new SequenceFile.Reader(fs, path, conf);
        Writable key = (Writable) ReflectionUtils.newInstance(reader.getKeyClass(), conf);
        Writable value = (Writable) ReflectionUtils.newInstance(reader.getValueClass(), conf);

        long position = reader.getPosition();
        while (reader.next(key, value)) {
            System.out.println("[" + key + "]=" + value);
        }

        IOUtils.closeStream(reader);
    }
}
