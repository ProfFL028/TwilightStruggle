import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.SequenceFile;
import org.apache.hadoop.io.Text;

import java.io.IOException;
import java.net.URI;


public class SequenceFileWriter {
    private static final String[] text = {
            "两行黄鹂鸣翠柳",
            "一行白鹭上青天"
    };

    public static void main(String[] args) throws IOException {
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(URI.create(args[0]), conf);
        Path path = new Path(args[0]);

        IntWritable key = new IntWritable();
        Text value = new Text();
        SequenceFile.Writer writer = SequenceFile.createWriter(fs, conf, path, key.getClass(), value.getClass());

        for (int i = 0; i < 100; i++) {
            key.set(100 - i);
            value.set(text[i % text.length]);
            writer.append(key, value);
        }
        IOUtils.closeStream(writer);
    }
}
