import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IOUtils;

import java.io.*;
import java.net.URI;

public class FileCopyFromLocal {
    public static void main(String[] args) throws IOException {
        String source = args[0]; // words
        String destination = args[1]; // hdfs://master:9000/input/words
        InputStream in = new BufferedInputStream(new FileInputStream(source));
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(destination), conf);
        OutputStream out = fs.create(new Path(destination));
        IOUtils.copyBytes(in, out, 4096, true);
    }
}
