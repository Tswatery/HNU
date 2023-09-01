package Lin.Hnu.Summer.Task1.DataDe;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

/*
* Keyin: LongWritable 单词在文本中的偏移量
* Valuein: Text 文本
* Keyout: Text
* Valueout: IntWritable
* */

public class DataDeMapper extends Mapper<LongWritable, Text, Text, NullWritable> {
    private IntWritable outV = new IntWritable(1);
    @Override
    protected void map(LongWritable key, Text value, Mapper<LongWritable, Text, Text, NullWritable>.Context context) throws IOException, InterruptedException {
        context.write(value, NullWritable.get()); // 直接写出就好了
    }
}
