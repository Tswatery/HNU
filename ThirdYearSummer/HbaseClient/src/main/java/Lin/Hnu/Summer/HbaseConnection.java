package Lin.Hnu.Summer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.client.Connection;
import org.apache.hadoop.hbase.client.ConnectionFactory;

import java.io.IOException;

public class HbaseConnection {
    // 多线程连接 类似于单例模式 统一使用一个连接
    // 声明一个静态属性
    public static Connection connection = null;
    static {
        // 1 创建同步（默认）连接
        try {
            // 使用读取本地文件的形式 在resources中的hbase-site.xml中
            connection = ConnectionFactory.createConnection();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    public static void closeConnection() throws IOException {
        // 判断连接是否为空
        if(connection != null)
            connection.close();
    }

    public static void main(String[] args) throws IOException {

//         Attention！ The following method is for one thread operation, which is not remanded.
//        1 创建配置对象
//        Configuration conf = new Configuration();
//        // 2 添加配置对象 在hbase-site.xml中配置的键值对 第一个是键 第二个是值 注意： 值不能使用空格隔开
//        conf.set("hbase.zookeeper.quorum", "hadoop102,hadoop103,hadoop104");
//        // 3 创建同步（默认）连接
//        Connection connection = ConnectionFactory.createConnection(conf);
//
//        // 4 使用连接
//        System.out.println(connection);
//
//        // 5 关闭连接
//        connection.close();

        // 直接使用创建好的连接 不在main线程中创建
        System.out.println(HbaseConnection.connection);

        // 关闭
        HbaseConnection.closeConnection();

    }
}
