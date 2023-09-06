package Lin.Hnu.Summer.Task2.Sort

import org.apache.spark.{SparkConf, SparkContext}

import java.io.FileOutputStream

object DataSort {
    def main(args: Array[String]): Unit = {
        // 1 set up connection
        val sparkConf = new SparkConf().setMaster("local").setAppName("DataSort")
        val sc = new SparkContext(sparkConf)

        // 2 run work

        // 2.1 read from file
        val lines = sc.textFile("D:\\IdeaProject\\Spark\\Spark\\input\\Task2\\input")
        // variable lines only have numbers

        // 2.2 put the same word into the same set
        val word_group = lines.groupBy(word => word)
        // 2.3 count
        val wordToCount = word_group.map {
            case (word, list) => {
                (word, list.size)
            }
        }

        val array = wordToCount.collect()

        val SortedArray = array.sortWith((a, b) => a._1.toInt < b._1.toInt)
        var cnt = 0
        val outputStream = new FileOutputStream("D:\\IdeaProject\\Spark\\Spark\\input\\Task2\\output\\output1")
        for (elem <- SortedArray) {
            cnt += 1
            val first = elem._1
            val second = elem._2
            val OutputString = s"$cnt $first\n"
            for(i <- 1 to second) {
                outputStream.write(OutputString.getBytes)
            }
        }
        outputStream.close()
        // 3 close
        sc.stop()
    }
}
