import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.lib.partition.HashPartitioner;

import java.io.IOException;

public class SecondarySort {
    public static class SecondaryMapper extends Mapper<LongWritable, Text, Text, NullWritable> {
        @Override
        protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
            context.write(value, NullWritable.get());
        }
    }

    public static class SecondaryReducer extends Reducer<Text, IntWritable, NullWritable, Text> {
        protected void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
            for (Text value : values) {
                context.write(NullWritable.get(), value);
            }
        }
    }

    public static class KeyPartitioner extends HashPartitioner<Text, NullWritable> {
        @Override
        public int getPartition(Text key, NullWritable value, int numReduceTasks) {
            return (key.toString().split(" ")[0].hashCode() & Integer.MAX_VALUE) % numReduceTasks;
        }
    }

    public static class SortComparator extends WritableComparator {
        protected SortComparator() {
            super(Text.class, true);
        }

        @Override
        public int compare(WritableComparable key1, WritableComparable key2) {
            String[] first = key1.toString().split(" ");
            String[] second = key2.toString().split(" ");

            if (first[0] == second[0]) {
                Integer l = Integer.parseInt(first[1]);
                Integer r = Integer.parseInt(second[1]);
                //return l.compareTo(r);
                if (l > r) {
                    return 1;
                } else if (l == r) {
                    return 0;
                } else {
                    return -1;
                }
            } else {
                Integer l = Integer.parseInt(first[0]);
                Integer r = Integer.parseInt(second[0]);
                // return l.compareTo(r);
                if (l > r) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "SecondarySort");
        job.setJarByClass(SecondarySort.class);
        job.setMapperClass(SecondarySort.SecondaryMapper.class);
        job.setReducerClass(SecondarySort.SecondaryReducer.class);
        job.setPartitionerClass(KeyPartitioner.class);
        job.setSortComparatorClass(SortComparator.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(NullWritable.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(NullWritable.class);
        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);

        FileSystem.get(conf).delete(new Path(args[1]), true);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        job.setNumReduceTasks(1); //important
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
