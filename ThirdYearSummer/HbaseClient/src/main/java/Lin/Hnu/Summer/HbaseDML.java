package Lin.Hnu.Summer;

import org.apache.hadoop.hbase.Cell;
import org.apache.hadoop.hbase.CellUtil;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.*;
import org.apache.hadoop.hbase.util.Bytes;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class HbaseDML {
    public static Connection connection = HbaseConnection.connection;
    public static String MyNameSpace = "HNUSummer", MyTableName = "Workers";

    /**
     *
     * @param namespace
     * @param tablename
     * @param rowKey 主键
     * @param columnFamily 列族名
     * @param columnName 列名
     * @param value 值
     */
    public static void PutData(String namespace, String tablename, String rowKey, String columnFamily, String columnName, String value) throws IOException {
        if(! HbaseDDL.isTableExists(namespace, tablename)) {
            System.out.printf("Table %s doesn't exist\n", tablename);
            return ;
        }
        // 1 If we want to change data in hbase, we should use connection.table
        Table table = connection.getTable(TableName.valueOf(namespace, tablename));

        // 2 Create object put
        Put put = new Put(Bytes.toBytes(rowKey));

        put.addColumn(Bytes.toBytes(columnFamily), Bytes.toBytes(columnName), Bytes.toBytes(value));
        try {
            table.put(put);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // close
        table.close();
    }

    /**
     * Read a data from a special column and a special row. A cell in other words.
     * @param namespace
     * @param tablename
     * @param rowKey
     * @param columnFamily
     * @param columnName
     */
    public static void GetData(String namespace, String tablename, String rowKey, String columnFamily, String columnName) throws IOException {
        Table table = connection.getTable(TableName.valueOf(namespace, tablename));

        Get get = new Get(Bytes.toBytes(rowKey));

        get.addColumn(Bytes.toBytes(columnFamily), Bytes.toBytes(columnName));
        try {
            Result result = table.get(get);
            Cell[] cells = result.rawCells();
            // print directly
            for (Cell cell : cells) {
                String s = new String(CellUtil.cloneValue(cell));
                System.out.println(s);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        connection.close();
    }

    public static void ReadFromFile() throws IOException {
        String filepath = "D:\\IdeaProject\\Hbase\\HbaseClient\\src\\static\\data.txt";
        BufferedReader bufferedReader = new BufferedReader(new FileReader(filepath));
        String line;
        // use regex to get KV pairs.
        String pattern = "\"(\\w+)\":\"([^\"]+)\"";
        Pattern compile = Pattern.compile(pattern);
        int cnt = 1;
        while((line = bufferedReader.readLine()) != null) {
            if(line.equals("[") || line.equals("]")) continue;
            Matcher matcher = compile.matcher(line);
            while(matcher.find()){
                String key = matcher.group(1), value = matcher.group(2);
                PutData(MyNameSpace, MyTableName, String.valueOf(cnt), "info", key, value);
            }
            cnt ++;
        }
        bufferedReader.close();
    }

    // 删除一行中的一列
    public static void DelData(String namespace, String tablename, String rowKey, String columnFamily, String columnName) throws IOException {
        Table table = connection.getTable(TableName.valueOf(namespace, tablename));
        Delete delete = new Delete(Bytes.toBytes(rowKey));
        delete.addColumn(Bytes.toBytes(columnFamily), Bytes.toBytes(columnName));
        try {
            table.delete(delete);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }


        connection.close();
    }

    public static void main(String[] args) throws IOException {
//        GetData(MyNameSpace, MyTableName, "25", "info", "work_order_no");
        DelData(MyNameSpace, MyTableName, "25", "info", "work_order_no");
    }

}
