if { $argc !=1 } {

       puts "Usage:ns tcpversion.tcl tcpversion"

       exit

}

 

set par1 [lindex $argv 0]

 

set ns [new Simulator]

#打开一个trace文件，用来记录数据报传送的过程

set nd [open $par1.tr w]

$ns trace-all $nd

#打开一个文件用来记录cwnd变化情况

set f0 [open cwnd-$par1.tr w]

 

#定义一个结束的程序

proc finish {} {

       global ns nd f0 tcp

puts [format "average throughput:%.1f Kbps" \ [expr [$tcp set ack_]*([$tcp set packetSize_])*8/1000/10]]

       $ns flush-trace

       close $nd

       close $f0

       exit 0

}

#定义一个记录的程序

proc record {} {

       global ns tcp f0

       set now [$ns now]

       puts $f0 "$now [$tcp set cwnd_]"

       $ns at [expr $now+0.01] "record"

}

 

#产生传送结点，路由器r1和r2和接收结点

set n0 [$ns node]

set r0 [$ns node]

set r1 [$ns node]

set n1 [$ns node]

#建立链路

$ns duplex-link $n0 $r0 20Mb 1ms DropTail

$ns duplex-link $r0 $r1 1Mb 4ms DropTail

$ns duplex-link $r1 $n1 20Mb 1ms DropTail

 

#设置队列长度为18个封包大小

set queue 18

$ns queue-limit $r0 $r1 $queue

 

#根据用户的设置，指定TCP版本，并建立相应的Agent

 if { $par1 == "Tahoe" } {

       set tcp [new Agent/TCP]

       set tcpsink [new Agent/TCPSink]

} elseif { $par1 == "Reno" } {

       set tcp [new Agent/TCP/Reno]

       set tcpsink [new Agent/TCPSink]

}

 

$ns attach-agent $n0 $tcp

$ns attach-agent $n1 $tcpsink

$ns connect $tcp $tcpsink

 

#建立FTP应用程序

set ftp [new Application/FTP]

$ftp attach-agent $tcp

 

$ns at 0.0 "$ftp start"

$ns at 10.0 "$ftp stop"

#在0.0s时调用record来记录TCP的cwnd 变化情况

$ns at 0.0 "record"

$ns at 10.0 "finish"

$ns run
