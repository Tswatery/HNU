package Lin.Hnu.Summer.Task3.AvgGrade;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

/**
 * Keyin 姓名
 * Valuein 当前人的成绩
 * Keyout 姓名
 * Valueout 平均成绩 注意是double
 */

public class AvgGradeReducer extends Reducer<Text, IntWritable, Text, DoubleWritable> {
    private DoubleWritable outV = new DoubleWritable();
    @Override
    protected void reduce(Text key, Iterable<IntWritable> values, Reducer<Text, IntWritable, Text, DoubleWritable>.Context context) throws IOException, InterruptedException {
        double grades = 0;
        Integer n = 0;
        for (IntWritable value : values) {
            String svalue = value.toString();
            grades += Integer.parseInt(svalue) * 1.0;
            n ++ ; // 统计个数
        }
        outV.set(grades / n);
        context.write(key, outV);
    }
}
