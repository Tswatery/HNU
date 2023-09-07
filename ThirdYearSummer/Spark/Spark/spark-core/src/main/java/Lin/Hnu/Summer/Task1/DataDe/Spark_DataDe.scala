package Lin.Hnu.Summer.Task1.DataDe

import org.apache.spark.{SparkConf, SparkContext}

import java.io.FileOutputStream

object Spark_DataDe {
    def main(args: Array[String]): Unit = {
        // 1 set up connection with spark
        val sparkConf = new SparkConf().setMaster("local").setAppName("DataDe")
        val sc = new SparkContext(sparkConf)

        // 2 run work

        // 2.1 read from file
        val lines = sc.textFile("D:\\IdeaProject\\Spark\\Spark\\input\\Task1\\input\\input1")
        // split line from "2012-3-1 a" to [2012-3-1, a]
        // 2.2 put the same word in the same set
        val word_group = lines.groupBy(word => word)
        // 2.3 count from each set
        val wordToCount = word_group.map {
            case (word, list) => {
                (word, list.size)
            }
        }
        val array = wordToCount.collect()

        // write to file
        val outputStream = new FileOutputStream("D:\\IdeaProject\\Spark\\Spark\\input\\Task1\\output\\output1")
        for(x <- array) {
            outputStream.write((x._1 + '\n').getBytes)
        }
        outputStream.close()
        // 3 close
        sc.stop()

    }
}
