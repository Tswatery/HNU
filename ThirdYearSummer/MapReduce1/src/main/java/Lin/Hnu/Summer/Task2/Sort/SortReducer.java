package Lin.Hnu.Summer.Task2.Sort;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

public class SortReducer extends Reducer<IntWritable, NullWritable, IntWritable, IntWritable> {
    private IntWritable outK = new IntWritable();
    private Integer cnt = 1;

    @Override
    protected void reduce(IntWritable key, Iterable<NullWritable> values, Reducer<IntWritable, NullWritable, IntWritable, IntWritable>.Context context) throws IOException, InterruptedException {
        outK.set(cnt);
        cnt ++;
        context.write(outK, key);
    }
}
