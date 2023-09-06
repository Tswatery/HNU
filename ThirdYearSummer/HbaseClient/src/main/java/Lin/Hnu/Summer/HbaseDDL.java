package Lin.Hnu.Summer;

import org.apache.hadoop.hbase.NamespaceDescriptor;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.Admin;
import org.apache.hadoop.hbase.client.ColumnFamilyDescriptorBuilder;
import org.apache.hadoop.hbase.client.Connection;
import org.apache.hadoop.hbase.client.TableDescriptorBuilder;
import org.apache.hadoop.hbase.util.Bytes;

import java.io.IOException;

public class HbaseDDL {
    // 声明一个静态属性 后续再其他类中使用该连接都会通过引用的方式来使用这个连接
    public static Connection connection = HbaseConnection.connection;

    /**
     * 创建命名空间
     * @param namespace
     */
    public static void CreateNameSpace(String namespace) throws IOException {
        /**
         * 1 Get class Admin.
         * There is an IO exception here, we don't deal with it until we finish all the code.
         * The connection of admin is light-weight and not thread-safe, so we can't use it in multiple threads.
         * In this way, pooling and caching are not remanded.
         */
        Admin admin = connection. getAdmin();

        /**
         * 2 Create namespace by using Class {@admin}
         * We should write a full description of namespace by using a lot of kV(key-value) pairs.
         */
        // 2.1 get namespace builder.
        NamespaceDescriptor.Builder builder = NamespaceDescriptor.create(namespace);

        // 2.2 Add KV pairs
        builder.addConfiguration("user", "lin"); // user -> lin

        /**
         *  2.3 Using builder.build to construct ===> designer scheme
         *  We can find that all IO exceptions are from this method. When the namespace already exists,
         *  the program will be stopped. So we just need to deal with it by using try-cache.
         */

        try {
            admin.createNamespace(builder.build()); // Also IO exception
        } catch (IOException e) {
            System.out.println("Namespace already exists");
            e.printStackTrace();
        }

        /**
         * 3 Close admin when finishing using.
         */
        admin.close();

    }

    /**
     * In hbase, we can use two parameters to describe a table, they are namespace and name of table.
     * This function can help us to find whether the table given exists.
     * @param namespace
     * @param tableName
     * @return true stands for exists
     */
    public static boolean isTableExists(String namespace, String tableName) throws IOException {
        // 1 get class admin
        Admin admin = connection.getAdmin();

        // 2 judge

        boolean result = false;
        try {
            result = admin.tableExists(TableName.valueOf(namespace, tableName));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // 3 close admin
        admin.close();

        // 3 return result
        return result;
    }

    /**
     * We should also use namespace and name of table to describe a table, and use name of columns to more precisely create a table.
     * @param namespace
     * @param tableName
     * @param columnFamilies
     */
    public static void CreateTable(String namespace, String tableName, String... columnFamilies) throws IOException {
        // In hbase, we should have at least one column. But the size of columnFamilies will be 0 if we use changeable args.
        // So we should check out whether its size is 0 before we start creating.
        if(columnFamilies.length == 0) {
            System.out.println("In hbase, we should have at least one column when creating table");
            return ;
        }

        // check whether table exists
        if(isTableExists(namespace, tableName)) {
            System.out.printf("The table %s already exists\n", tableName);
            return ;
        }

        // 1 get admin
        Admin admin = connection.getAdmin();


        // 2 Use method to create table

        // 2.1 Create builder of table
        TableDescriptorBuilder tableDescriptorBuilder = TableDescriptorBuilder.newBuilder(TableName.valueOf(namespace, tableName));

        // 2.2 add information
        for (String columnFamily : columnFamilies) {
            // 2.3 create column family description
            ColumnFamilyDescriptorBuilder columnFamilyDescriptorBuilder = ColumnFamilyDescriptorBuilder.newBuilder(Bytes.toBytes(columnFamily));
            // 2.4 add
            columnFamilyDescriptorBuilder.setMaxVersions(3);

            tableDescriptorBuilder.setColumnFamily(columnFamilyDescriptorBuilder.build());
        }


        try {
            admin.createTable(tableDescriptorBuilder.build());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        System.out.printf("Table %s successfully creates\n", tableName);

        // 3 close
        admin.close();
    }


    public static boolean DeleteTable(String namespace, String tablename) throws IOException {
        if(! isTableExists(namespace, tablename)) {
            System.out.printf("Table %s doesn't exist, can't be deleted\n", tablename);
            return false;
        }
        Admin admin = connection.getAdmin();
        try {
            // We should make table disable before deleting it.
            TableName tableName = TableName.valueOf(namespace, tablename);
            admin.disableTable(tableName);
            admin.deleteTable(tableName);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        System.out.printf("Table %s deletes successfully\n", tablename);
        admin.close();
        return true;
    }

    public static void main(String[] args) throws IOException {
        // Test the method we create above.
        DeleteTable("HNUSummer", "Workers");
        CreateTable("HNUSummer", "Workers", "info");

        HbaseConnection.closeConnection();
    }
}
