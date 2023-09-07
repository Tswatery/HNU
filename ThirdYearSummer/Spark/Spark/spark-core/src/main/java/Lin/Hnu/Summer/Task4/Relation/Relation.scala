package Lin.Hnu.Summer.Task4.Relation

import org.apache.spark.{SparkConf, SparkContext}

import java.io.FileOutputStream
import scala.collection.mutable

object Relation {
    def main(args: Array[String]): Unit = {
        // 1 set up connection
        val sparkConf = new SparkConf().setMaster("local").setAppName("Relation")
        val sc = new SparkContext(sparkConf)

        // 2 run work

        // 2.1 read from file
        val lines = sc.textFile("D:\\IdeaProject\\Spark\\Spark\\input\\Task4\\input")
        val ActuralLines = lines.collect()

        // 2.2 split each line
        val SonParent = new mutable.HashMap[String, Array[String]]()
        val ParentSon = new mutable.HashMap[String, Array[String]]()
        val ParentSet = new mutable.HashSet[String]()
        for(line <- ActuralLines ){
            val words = line.split("\\s+")
            var son = words(0)
            var parent = words(1)
            ParentSet += parent
            if(SonParent.contains(son)) {
                SonParent(son) = SonParent(son) :+ parent
            }else {
                SonParent(son) = Array(parent)
            }
            if(ParentSon.contains(parent)) {
                ParentSon(parent) = ParentSon(parent) :+ son
            }else {
                ParentSon(parent) = Array(son)
            }
        }
        val OutputStream = new FileOutputStream("D:\\IdeaProject\\Spark\\Spark\\input\\Task4\\output\\output")
        OutputStream.write("GrandSon GrandParent\n".getBytes)
        for(x <- ParentSet) {
            if( ParentSon.contains(x)) {
                for (grandson <- ParentSon(x)) {
                    if(SonParent.contains(x)) {
                        for (grandparent <- SonParent(x)) {
                            val OutputString = s"$grandson    $grandparent\n"
                            OutputStream.write(OutputString.getBytes)
                        }
                    }
                }
            }
        }
        OutputStream.close()
        // 3 close
        sc.stop()
    }
}
