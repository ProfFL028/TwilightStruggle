import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;

import java.io.IOException;
import java.net.URI;

public class CreateDir {
    public static void main(String[] args) throws IOException {
        String uri = args[0]; // hdfs://master:9000/input/test
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(uri), conf);
        Path dfs = new Path("hdfs://master:9000/user/test");
        fs.mkdirs(dfs);
    }
}
