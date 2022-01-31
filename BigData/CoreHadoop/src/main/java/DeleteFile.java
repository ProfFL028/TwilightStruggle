import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;

import java.io.IOException;
import java.net.URI;

public class DeleteFile {
    public static void main(String[] args) throws IOException {
        String uri = args[0]; // hdfs://master:9000/user/test
        Configuration conf = new Configuration();

        FileSystem fs = FileSystem.get(URI.create(uri), conf);
        String path = uri.substring(0, uri.lastIndexOf("/"));
        Path delPath = new Path(path);
        boolean isDeleted = fs.delete(delPath, false);
        // boolean isDeleted = fs.delete(delPath, true); // recursively
        System.out.println(uri + " deleted: " + isDeleted);
    }
}
