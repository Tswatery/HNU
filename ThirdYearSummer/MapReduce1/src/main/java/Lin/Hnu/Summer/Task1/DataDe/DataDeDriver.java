package Lin.Hnu.Summer.Task1.DataDe;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import java.io.IOException;

public class DataDeDriver{
    public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException {
        // 1 获取job
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf);

        // 设置jar包路径
        job.setJarByClass(DataDeDriver.class);

        //3 关联mapper和reducer
        job.setMapperClass(DataDeMapper.class);
        job.setReducerClass(DataDeReducer.class);

        // 4 设置map的输出kv类型
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(NullWritable.class);

        // 5 设置最终输出的kv类型
        job.setOutputValueClass(Text.class);
        job.setOutputValueClass(NullWritable.class);

        // 6设置输入路径以及输出路径
        FileInputFormat.setInputPaths(job, new Path("D:\\IdeaProject\\MapReduce1\\input\\Task1\\Input"));
        FileOutputFormat.setOutputPath(job, new Path("D:\\IdeaProject\\MapReduce1\\input\\Task1\\Output"));

        // 7 提交job
        boolean result = job.waitForCompletion(true);

        System.exit(result ? 0 : 1);
    }
}
