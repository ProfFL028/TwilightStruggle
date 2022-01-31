import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;

import java.io.IOException;
import java.net.URI;

public class CheckFileIsExists {
    public static void main(String[] args) throws IOException {
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(args[0]), conf);
        Path path = new Path(args[0]);
        boolean isExists = fs.exists(path);
        System.out.println("File: " + args[0] + " isExists? " + isExists);
    }
}
