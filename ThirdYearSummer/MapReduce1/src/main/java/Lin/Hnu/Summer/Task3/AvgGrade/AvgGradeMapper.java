package Lin.Hnu.Summer.Task3.AvgGrade;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

/**
 * Keyin: 偏移量
 * Valuein: 文本的一行
 * Keyout: 姓名
 * Valueout: 当前人的成绩
 */
public class AvgGradeMapper extends Mapper<LongWritable, Text, Text, IntWritable> {
    private Text outK = new Text();
    private IntWritable outV = new IntWritable();
    @Override
    protected void map(LongWritable key, Text value, Mapper<LongWritable, Text, Text, IntWritable>.Context context) throws IOException, InterruptedException {
        String line = value.toString();
        String[] words = line.split("    ");

        outK.set(words[0]);
        outV.set(Integer.parseInt(words[1]));
        context.write(outK, outV);
    }
}
