package Lin.Hnu.Summer.wc

import org.apache.spark.{SparkConf, SparkContext}

object Spark01_WordCount {
    def main(args: Array[String]): Unit = {
        // 1 set up connection with spark
        val sparkConf = new SparkConf().setMaster("local").setAppName("WordCount")
        val sc = new SparkContext(sparkConf)

        // 2 run work
        // 2.1 read from your file, line by line default.
        val lines = sc.textFile("D:\\IdeaProject\\Spark\\Spark\\input\\test")
        // 2.2 split each line  "hello world" => [hello, world]
        val words = lines.flatMap(_.split(" ")) // 扁平化操作 整体到个体
        // 2.3 put the same word in the same set    [hello, hello]  [world, world]
        val word_group = words.groupBy(word => word) // a tuple. first one is word, second one is an iterable variable
        // 2.4 count from each set and change the set  [hello, hello] => [hello, 2]
        val wordToCount = word_group.map{
            case(word, list) => {
                (word, list.size)
            }
        }
        // 2.5 print result
        val tuples = wordToCount.collect()
        tuples.foreach(println)
        // 3 close connection
        sc.stop()
    }
}
