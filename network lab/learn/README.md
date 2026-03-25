# Network Lab - Quick Reference

## How to compile and run

All C programs: `gcc filename.c -o out && ./out`  
For client-server: always start **server first**, then client in a new terminal.

---

## Exp 3 - TCP Chat (Bidirectional)

**Concept:** Two-way text chat over TCP.  
**Steps:** socket -> bind -> listen -> accept (server) | socket -> connect (client)

```
gcc server.c -o server && ./server
gcc client.c -o client && ./client
```
Type `stop` to end the session.

---

## Exp 4 - TCP: Square of Number

**Concept:** Client sends a n, server returns its square.  
Same TCP flow as Exp 3, but server does `num * num` and sends back.

```
gcc server.c -o server && ./server
gcc client.c -o client && ./client
```

---

## Exp 5 - TCP File Transfer

**Concept:** Client sends a filename, server reads and sends that file's contents.  
Server uses `fopen` + `fgets` loop to stream the file.

```
gcc server.c -o server && ./server
gcc client.c -o client && ./client
```

---

## Exp 6 - UDP Chat

**Concept:** Same as Exp 3 but using UDP (no connection).  
Key difference: `SOCK_DGRAM` instead of `SOCK_STREAM`, `sendto`/`recvfrom` instead of `send`/`read`. No `connect`/`accept`.

```
gcc server.c -o server && ./server
gcc client.c -o client && ./client
```

---

## Exp 9 - Selective Repeat ARQ

**Concept:** Sender sends a window of frames. Receiver randomly drops some (simulating errors). Sender retransmits only the dropped ones (not the whole window).

```
gcc receiver.c -o receiver && ./receiver   # terminal 1
gcc sender.c -o sender && ./sender         # terminal 2
```
Enter N (total frames) and window s when prompted.

---

## Exp 10 - Leaky Bucket

**Concept:** Incoming packets fill a bucket. Bucket drains at fixed `output_rate`. If packet doesn't fit, excess is rejected.

```
gcc exp10.c -o exp10 && ./exp10
```
Bucket s = 10, Output rate = 7 (hardcoded). Enter packet s each second.

| Condition | Action |
|---|---|
| pkt <= remaining space | Accept, drain output_rate |
| pkt > remaining space | Reject overflow portion |

---

## Exp 11 - Distance Vector Routing

**Concept:** Each node builds a shortest-path table using Bellman-Ford. Nodes update via neighbors until no changes happen.

```
gcc exp11.c -o exp11 && ./exp11
```
Input: n of nodes, n of links, then each link as `start end cost`.

---

## Exp 13 - NS2 Simulation (TCL)

**Concept:** 4-node topology. TCP/FTP from n0 to n3, UDP/CBR from n1 to n3, both going through bottleneck n2-n3 link.

```
ns exp13.tcl
```
Opens NAM visualizer automatically. Blue = TCP flow, Red = UDP flow.

**Topology:**
```
n0 --2Mb/10ms--> n2 --1.7Mb/20ms--> n3
n1 --2Mb/10ms--/
```

---

## TCP vs UDP - Key Difference

| Feature | TCP (Exp 3,4,5) | UDP (Exp 6,9) |
|---|---|---|
| Socket type | `SOCK_STREAM` | `SOCK_DGRAM` |
| Connection | Yes (`connect`/`accept`) | No |
| Send/Receive | `send`/`read` | `sendto`/`recvfrom` |
| Reliability | Guaranteed | Not guaranteed |