if { $argc !=1 } {

       puts "Usage:ns tcpversion.tcl tcpversion"

       exit

}

 

set par1 [lindex $argv 0]

 

set ns [new Simulator]

#��һ��trace�ļ���������¼���ݱ����͵Ĺ���

set nd [open $par1.tr w]

$ns trace-all $nd

#��һ���ļ�������¼cwnd�仯���

set f0 [open cwnd-$par1.tr w]

 

#����һ�������ĳ���

proc finish {} {

       global ns nd f0 tcp

puts [format "average throughput:%.1f Kbps" \ [expr [$tcp set ack_]*([$tcp set packetSize_])*8/1000/10]]

       $ns flush-trace

       close $nd

       close $f0

       exit 0

}

#����һ����¼�ĳ���

proc record {} {

       global ns tcp f0

       set now [$ns now]

       puts $f0 "$now [$tcp set cwnd_]"

       $ns at [expr $now+0.01] "record"

}

 

#�������ͽ�㣬·����r1��r2�ͽ��ս��

set n0 [$ns node]

set r0 [$ns node]

set r1 [$ns node]

set n1 [$ns node]

#������·

$ns duplex-link $n0 $r0 20Mb 1ms DropTail

$ns duplex-link $r0 $r1 1Mb 4ms DropTail

$ns duplex-link $r1 $n1 20Mb 1ms DropTail

 

#���ö��г���Ϊ18�������С

set queue 18

$ns queue-limit $r0 $r1 $queue

 

#�����û������ã�ָ��TCP�汾����������Ӧ��Agent

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

 

#����FTPӦ�ó���

set ftp [new Application/FTP]

$ftp attach-agent $tcp

 

$ns at 0.0 "$ftp start"

$ns at 10.0 "$ftp stop"

#��0.0sʱ����record����¼TCP��cwnd �仯���

$ns at 0.0 "record"

$ns at 10.0 "finish"

$ns run
