import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;

import java.io.IOException;
import java.net.URI;

public class ListFiles {
    public static void main(String[] args) throws IOException {
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(args[0]), conf);
        Path path = new Path(args[0]);
        FileStatus status[] = fs.listStatus(path);
        for (int i = 0; i < status.length; i++) {
            System.out.println(status[i].getPath().toString());
        }
    }
}
