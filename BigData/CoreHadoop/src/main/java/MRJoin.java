import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class MRJoin {
    public static class MRJoinMapper extends Mapper<LongWritable, Text, Text, Text> {
        @Override
        protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
            String filePath = ((FileSplit) context.getInputSplit()).getPath().toString();

            String joinKey = null;
            String joinValue = null;
            String[] keyValue = value.toString().split("\t");
            if (keyValue.length == 2) {
                String fileFlag = "l";
                if (filePath.contains("students_info")) {
                    joinKey = keyValue[1];
                    joinValue = keyValue[0];
                } else {
                    fileFlag = "r";
                    joinKey = keyValue[0];
                    joinValue = keyValue[1];
                }
                context.write(new Text(joinKey), new Text(joinValue + "\t" + fileFlag));
            }
        }
    }

    public static class MRJoinReducer extends Reducer<Text, Text, Text, Text> {
        @Override
        protected void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
            Iterator<Text> iterator = values.iterator();
            List<String> studentClassNames = new ArrayList<>();
            String studentName = "";

            while (iterator.hasNext()) {
                String vv = iterator.next().toString();
                String[] infos = vv.split("\t");

                System.out.println(infos[0] + "|" + infos[1].trim() + "|");

                if (infos[1].trim().equals("l")) {
                    studentName = infos[0].trim();
                } else {
                    studentClassNames.add(infos[0].trim());
                }
            }
            for (int i = 0; i < studentClassNames.size(); i++) {
                context.write(new Text(studentName), new Text(studentClassNames.get(i)));
            }
        }
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "MRJoin");
        job.setJarByClass(MRJoin.class);
        job.setMapperClass(MRJoin.MRJoinMapper.class);
        job.setReducerClass(MRJoin.MRJoinReducer.class);
        job.setOutputFormatClass(TextOutputFormat.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        FileSystem.get(conf).delete(new Path(args[1]), true);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
