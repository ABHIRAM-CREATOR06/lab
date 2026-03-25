# EXP 13 - NS2 Network Simulation
# Simulates 4 nodes: n0 and n1 send traffic to n3 through n2
# n0 -> n2 -> n3 : TCP/FTP traffic  (shown in Blue)
# n1 -> n2 -> n3 : UDP/CBR traffic  (shown in Red)
# Run: ns exp13.tcl

# --- Setup ---
set ns [new Simulator]

# Color the flows for NAM visualization
$ns color 1 Blue
$ns color 2 Red

# Open NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

# Finish procedure: flush trace and open NAM
proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam out.nam &
    exit 0
}

# --- Create 4 Nodes ---
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# --- Create Links ---
# n0 and n1 connect to n2 (2Mbps, 10ms delay)
# n2 connects to n3 (1.7Mbps bottleneck, 20ms delay)
$ns duplex-link $n0 $n2 2Mb  10ms DropTail
$ns duplex-link $n1 $n2 2Mb  10ms DropTail
$ns duplex-link $n2 $n3 1.7Mb 20ms DropTail

# Set queue limit on bottleneck link
$ns queue-limit $n2 $n3 10

# --- NAM Layout (node positions) ---
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n2 $n3 queuePos 0.5

# --- TCP + FTP (n0 -> n3) ---
set tcp  [new Agent/TCP]
set sink [new Agent/TCPSink]
$tcp set class_ 2
$tcp set fid_ 1
$ns attach-agent $n0 $tcp
$ns attach-agent $n3 $sink
$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

# --- UDP + CBR (n1 -> n3) ---
set udp  [new Agent/UDP]
set null [new Agent/Null]
$udp set fid_ 2
$ns attach-agent $n1 $udp
$ns attach-agent $n3 $null
$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_        CBR
$cbr set packet_size_ 1000
$cbr set rate_        1mb
$cbr set random_      false

# --- Schedule Events ---
$ns at 0.1 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"
$ns at 4.5 "$ns detach-agent $n0 $tcp ; $ns detach-agent $n3 $sink"
$ns at 5.0 "finish"

# --- Print info and Run ---
puts "CBR packet s = [$cbr set packet_size_]"
puts "CBR interval    = [$cbr set interval_]"
$ns run