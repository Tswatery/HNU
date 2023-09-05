package Lin.Hnu.Summer.Task2;


import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.LocatedFileStatus;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.fs.RemoteIterator;
import org.apache.hadoop.io.IOUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.net.URISyntaxException;

/**
 * 1 获取一个客户端对象
 * 2 执行相关命令
 * 3 关闭资源
 */
public class HdfsClient {
    private FileSystem fs;
    @Before
    public void init() throws URISyntaxException, IOException, InterruptedException {
        // 连接集群的namenode地址
        URI uri = new URI("hdfs://hadoop102:8020");// hadoop102内部的通信端口是8020
        // 创建一个配置文件
        Configuration configuration = new Configuration();

        // 指定用户
        String usr = "lin";

        // 1 拿到客户端对象
        fs = FileSystem.get(uri, configuration, usr);
    }
    @After
    public void close() throws IOException {
        fs.close();
    }
    @Test
    public void Filemkdir() throws URISyntaxException, IOException, InterruptedException {
        //获取资源
        init();
        // 2 创建一个文件夹
        fs.mkdirs(new Path("/testmkdir"));
        // 3 关闭资源
        close();
    }

    @Test
    public void FileRmdir() throws URISyntaxException, IOException, InterruptedException {
        init();
        /**
         * @param1: file path
         * @param1: Whether to delete directory recursively
         */
        fs.delete(new Path("/testmkdir"), true);
        close();
    }
    @Test
    public void FileUpload() throws URISyntaxException, IOException, InterruptedException {
        init();
        /**
         * @param1: Boolean Whether to delete source file
         * @param2: Boolean Whether to overwrite destination file if already exists
         * @param3: Path of source file
         * @param4: Path of destination file
         */
        fs.copyFromLocalFile(false, false, new Path("D:\\IdeaProject\\MapReduce1\\input\\Task1\\Input\\input1"), new Path( "/"));
        close();
    }

    @Test
    public void FileDetail() throws IOException, URISyntaxException, InterruptedException {
        init();
        /**
         * @param1: path of file
         * @param2: Whether recursively
         */
        RemoteIterator<LocatedFileStatus> files = fs.listFiles(new Path("/input1"), true);

        // 遍历
        while (files.hasNext()) {
            LocatedFileStatus fileStatus = files.next();
            if(fileStatus.isFile()){
                Path path = fileStatus.getPath();
                System.out.printf("File name is %s\n", fileStatus.getPath().getName());
                fs.open(path);
                InputStream in = fs.open(path);
                IOUtils.copyBytes(in, System.out, 2048, false);
            }
        }
        close();
    }
}
