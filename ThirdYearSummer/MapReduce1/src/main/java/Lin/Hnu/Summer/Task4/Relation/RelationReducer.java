package Lin.Hnu.Summer.Task4.Relation;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;
import java.util.ArrayList;

public class RelationReducer extends Reducer<Text, Text, Text, Text> {
    private String MapoutV;
    private Text outK = new Text();
    private Text outV = new Text();
    @Override
    protected void reduce(Text key, Iterable<Text> values, Reducer<Text, Text, Text, Text>.Context context) throws IOException, InterruptedException {
        ArrayList<String> grandparents = new ArrayList<>();
        ArrayList<String> grandsons = new ArrayList<>();
        for (Text value : values) {
            MapoutV = value.toString(); // ["Tom 0", "Alice 1"]
            String[] words = MapoutV.split(" ");
            String t1 = words[0], t2 = words[1];
            if(t2.equals("1")) { // 表明是子父关系 MapoutK 是儿子 MapoutV是父亲 Alice是爷爷
                grandparents.add(t1);
            }else { // 表明是父子关系 MapoutK是父亲 MapoutV是儿子 Tom是孙子
                grandsons.add(t1);
            }
        }
        for (String grandson : grandsons) {
            for (String grandparent : grandparents) {
                outK.set(grandson);
                outV.set(grandparent);
                context.write(outK, outV);
            }
        }
    }
}
