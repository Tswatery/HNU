package Lin.Hnu.Summer.Task4.Relation;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

// Tom Jack

/**
 * Keyout: 父亲的名字                         | 儿子的名字
 * Valueout: 儿子的名字 + '0' 表示是父子关系    | 父亲的名字 + '1'
 */
public class RelationMapper extends Mapper<LongWritable, Text, Text, Text> {
    private Text outV = new Text();
    private Text outK = new Text();
    private String tmpv;
    @Override
    protected void map(LongWritable key, Text value, Mapper<LongWritable, Text, Text, Text>.Context context) throws IOException, InterruptedException {
        String line = value.toString();
        String[] words = line.split("        ");
        // Tom Jack
        tmpv = String.format("%s %d", words[1], 1); // 表示是子父关系 <Tom, "Jack 1">
        outK.set(words[0]);
        outV.set(tmpv);
        context.write(outK, outV);
        outK.set(words[1]);
        tmpv = String.format("%s %d", words[0], 0); // 表示是父子关系 <Jack, "Tom 0">
        outV.set(tmpv);
        context.write(outK, outV);
    }
}
