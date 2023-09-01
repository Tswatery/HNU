package Lin.Hnu.Summer.Task3.AvgGrade;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import java.io.IOException;

public class AvgGradeDriver {
    public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException {
        // 1 获取job
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf);

        // 2 设置jar包路径
        job.setJarByClass(AvgGradeDriver.class);

        // 3 关联 mapper 和 reducer
        job.setMapperClass(AvgGradeMapper.class);
        job.setReducerClass(AvgGradeReducer.class);

        // 4 设置mapper输出kv
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(IntWritable.class);

        // 5 设置 reducer输出kv
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(DoubleWritable.class);

        // 6 设置输入输出路径
        FileInputFormat.setInputPaths(job, new Path("D:\\IdeaProject\\MapReduce1\\input\\Task3\\input"));
        FileOutputFormat.setOutputPath(job, new Path("D:\\IdeaProject\\MapReduce1\\input\\Task3\\output"));

        // 7 提交job
        boolean result = job.waitForCompletion(true);
        System.exit(result ? 0 : 1);
    }
}
