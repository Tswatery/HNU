package Lin.Hnu.Summer.Task4.Relation;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import java.io.IOException;

public class RelationDriver {
    public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException {
        // 1 获取job
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf);

        // 2 设置jar包路径
        job.setJarByClass(RelationDriver.class);

        // 3 关联mapper以及reducer
        job.setMapperClass(RelationMapper.class);
        job.setReducerClass(RelationReducer.class);

        // 4 设置mapper输出格式
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(Text.class);

        // 5 设置reducer输出格式
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);

        // 6 设置输入输出路径
        FileInputFormat.setInputPaths(job, new Path("D:\\IdeaProject\\MapReduce1\\input\\Task4\\input"));
        FileOutputFormat.setOutputPath(job, new Path("D:\\IdeaProject\\MapReduce1\\input\\Task4\\output"));

        // 7 提交job
        boolean result = job.waitForCompletion(true);
        System.exit(result ? 0 : 1);
    }
}
