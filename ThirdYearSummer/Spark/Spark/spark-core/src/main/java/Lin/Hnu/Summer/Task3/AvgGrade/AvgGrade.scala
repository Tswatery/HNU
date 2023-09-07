package Lin.Hnu.Summer.Task3.AvgGrade

import org.apache.spark.{SparkConf, SparkContext}

import java.io.FileOutputStream
import scala.collection.mutable

object AvgGrade {

    def StrToInt(str: String): Int = {
        val regex = """([0-9]+)""".r
        val res = str match {
            case regex(num) => num
            case _ => "-1"
        }
        val result = Integer.parseInt(res)
        result
    }

    def main(args: Array[String]): Unit = {
        // 1 set up connection
        val sparkConf = new SparkConf().setMaster("local").setAppName("AvgGrade")
        val sc = new SparkContext(sparkConf)

        // 2 run work

        // 2.1 read from file
        val lines = sc.textFile("D:\\IdeaProject\\Spark\\Spark\\input\\Task3\\input")
        val ActualLines = lines.collect()
        // split lines, the variable words is iterable
        val MyCount = new mutable.HashMap[String, Tuple2[Integer, Integer]]()
        for(line <- ActualLines) {
            val words = line.split("\\s+")
            val key = words(0)
            val value = StrToInt(words(1))
            if(MyCount.contains(key)) {
                MyCount(key) = (MyCount(key)._1 + value, MyCount(key)._2 + 1)
            } else {
                MyCount(key) = (value, 1)
            }
        }
        // get average grade
        val outputStream = new FileOutputStream("D:\\IdeaProject\\Spark\\Spark\\input\\Task3\\output\\output1")
        outputStream.write("Name AvgGrade\n".getBytes)
        for((name, tuple) <- MyCount) {
            val AvgGrade = tuple._1 * 1.0 / tuple._2
            val OutputString = s"$name $AvgGrade\n"
            outputStream.write(OutputString.getBytes)
        }
        outputStream.close()

        // 3 close
        sc.stop()
    }
}
