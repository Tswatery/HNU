package Lin.Hnu.Summer.Task1.DataDe;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;


/**
 * Keyin: map阶段的keyout  即 text
 * Valuein: map阶段的valueout 即IntWritable
 * Keyout: Text
 * Valueout: NullWritable
 */
public class DataDeReducer extends Reducer<Text, IntWritable, Text, NullWritable>{
    @Override
    protected void reduce(Text key, Iterable<IntWritable> values, Reducer<Text, IntWritable, Text, NullWritable>.Context context) throws IOException, InterruptedException {
        context.write(key, NullWritable.get());
    }
}
