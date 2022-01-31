import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.BlockLocation;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;

import java.io.IOException;
import java.net.URI;

public class LocationFile {
    public static void main(String[] args) throws IOException {
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(args[0]), conf);
        Path path = new Path(args[0]);
        FileStatus fileStatus = fs.getFileStatus(path);
        BlockLocation[] blockLocations = fs.getFileBlockLocations(fileStatus, 0, fileStatus.getLen());
        int blockLen = blockLocations.length;
        for (int i = 0; i < blockLen; i++) {
            String[] hosts = blockLocations[i].getHosts();
            System.out.println("block_" + i + "_location:" + hosts[0]);
        }
    }
}
