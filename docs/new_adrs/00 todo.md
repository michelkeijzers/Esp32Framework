GENERIC

vscode
rtos ticks
esp32 c3 choice
multiple esp32 choice, nodes
multiple equal nodes for more of the same functionality

different roles
all nodes except webserver common
boot before master
esp-now between nodes, max 250 bytes, sequence number, version field, crc, static key , splitting because of 250 bytes, encryption set by user in website, distributed by master.

```
- senderNodeId                1 byte
- senderNodeSequenceNumber    1 byte
- receiverNodeId              1 byte
- receiverNodeSequenceNumber  1 byte
- messageSequenceNumber       1 byte
- packageNumber               1 byte (e.g. 0-2 for 3 DMX universe packages)
- length                      2 bytes (incl payload header)
- version                     3 bytes
- reserved                    1 byte
- crc                         2 bytes
- Reserved:                   6 bytes
  Total                      20 bytes
- <payload: up to 230 bytes> for dmx values:
  -              Package 1            Package 2           Package 3
  - universeId:      1 byte
  - enabled:         1 byte
  - fileName:       32 bytes
  - name:           32 bytes
  - dmxValues:     160 bytes         200 bytes            152 bytes
- total:           224 bytes         200 bytes            152 bytes
```

ota- dual partition, triggerable from website, 16 bits crc, crc per chucnk and total (?), resending, and chunk per chunk
rtos priorities

nodes software folders, common node software
dependency injection for testing, esp32 mocks for testing
nfs write frequency
rtos tasks
configuration/nvs structure will be equal between projects
littlefs file structure will be equal between projects
logging with debug level, add to website and api contract
cmake lists
unit testing , api tester
integration testing

sub folders
tasks: every node has a master task, esp-now task, logging task, ota task and optionally other node specific tasks.

DMX
DMX-REQ-051: Individual node power budgets: Master ~80mA, Webserver ~120mA, Input ~80mA, Display ~80mA, DMX ~80mA (baseline).
power: enough current, 5V, 220-240V, 50-60Hz

WEB SERVER

per project, only code changing + website
shall spread out messages among tasks/master etc.
sends mac address to master
htmx, pico.css
sta + ap mode
sending status updates with SSE
webserver authentication/security
wpa2
ota on sta mode
tasks only chat via main task

MASTER

Master checks that all nodes are compatible
routing; Master maintains routing table of MAC addresses to node roles, store in nvs
nodes only task via master and to or from webserver, not directly to each other, exception for time critical messages that can be sent directly to destination without passing through webserver
watch dog. grace period for boot for watchdogs of other nodes.
esp-now: spreading esp now key and restart using new key

DMX
Max3485

DISPLAY
controller: TM1637
index file(s)
