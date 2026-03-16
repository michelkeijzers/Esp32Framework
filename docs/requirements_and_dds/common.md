# COMMON REQUIREMENTS AND DESIGN DECISIONS

# Roles

## Role Types

**REQ-GEN-100:** The system shall support four roles: ROLE_MASTER, ROLE_REMOTE, ROLE_WEBSERVER, ROLE_NODE.<br/>
**Rationale:** Defines the different roles each ESP can assume in the system.<br/>
**Alternative considered:** Fewer or more roles — rejected, would limit flexibility or add unnecessary complexity.

## Fixed Roles

**REQ-GEN-110:** The role of each ESP shall be determined at compile time. No runtime role switching.<br/>
**Rationale:** Roles are static per project — no need for dynamic switching. Compile time configuration simplifies implementation and reduces attack surface.<br/>
**Alternative considered:** Runtime role switching — rejected, adds complexity and potential for misconfiguration.

## Master and Remote are Common

**REQ-GEN-120:** Master and remote role code shall be fully common (equal) between projects — no project specific code, never reflashed between projects.<br/>
**Rationale:** Master is a blind router, remote is a simple heartbeat sender — both roles are common across projects and do not require project specific logic.<br/>
**Alternative considered:** Per-project master and remote code — rejected, would fragment codebase and lose reusability.

# ESP-NOW Protocol

## For Inter-ESP communication

**REQ-GEN-200:** ESP-NOW shall be used for all inter-ESP communication — no Wi-Fi or Bluetooth connections between ESPs.<br/>
**Rationale:** ESP-NOW provides low-latency, connectionless communication ideal for real-time performance use. Avoids Wi-Fi overhead and complexity.<br/>
**Alternative considered:** Wi-Fi or Bluetooth — rejected, higher latency and complexity, not suitable for real-time performance.

## Payload

**REQ-GEN-210:** Maximum ESP-NOW message payload shall not exceed 250 bytes — hard protocol limit.<br/>
**Rationale:** ESP-NOW has a maximum payload size of 250 bytes. Messages must be designed to fit within this limit.<br/>
**Alternative considered:** Larger messages with fragmentation — rejected, adds complexity and latency.

## Sequence Numbers

**REQ-GEN-220:** All ESP-NOW messages shall include a sequence number to detect lost or duplicate messages.<br/>
**Rationale:** ESP-NOW does not guarantee delivery or ordering. Sequence numbers allow receivers to detect and handle lost or duplicate messages appropriately.<br/>
**Alternative considered:** No sequence numbers — rejected, would have no way to detect lost or duplicate messages, impacting reliability.

## Version Field

**REQ-GEN-230:** All ESP-NOW messages shall include a version field to support future firmware compatibility.<br/>
**Rationale:** Allows for future firmware updates on individual nodes without breaking message compatibility with other nodes on different firmware versions.<br/>
**Alternative considered:** No version field — rejected, would risk compatibility issues as firmware evolves.

## CRC16 Checksum

**REQ-GEN-240:** All ESP-NOW messages shall include a CRC16 checksum calculated over the full message including payload — corrupted messages shall be silently discarded.<br/>
**Rationale:** ESP-NOW transmission can corrupt data — silent corruption is worse than a dropped message. CRC16 allows receivers to detect corrupted messages and discard them without processing invalid data.<br/>
**Alternative considered:** No CRC — rejected, would risk silent data corruption leading to unpredictable behavior.

## Queue Overflow Strategy

**REQ-GEN-250:** Queue overflow strategy shall be defined — drop oldest or drop newest — and documented per queue.<br/>
**Rationale:** In high traffic scenarios, queues may become full. A defined strategy for handling overflow ensures predictable behavior under load.<br/>
**Alternative considered:** No defined strategy — rejected, would lead to unpredictable behavior when queues are full.

# Security

## Static Key Encryption

**REQ-SEC-300:** ESP-NOW static Key encryption shall be used.<br/>
**Rationale:** ESP-NOW messages are transmitted over the air and can be intercepted. Static Key encryption provides a basic level of security to prevent unauthorized interception and tampering of messages.<br/>
**Alternative considered:** No encryption — rejected, would leave messages vulnerable to interception and tampering. Dynamic keys or more advanced encryption — rejected, adds complexity and is not strictly necessary for hobby use. Key management can be handled securely via NVS and physical access to devices. Obfuscation of key in code can provide additional security through obscurity, but no private data is sent. Application-Level security (magic number in message) is not as good as static keys.

## Configurable Static Key in NVS

**REQ-SEC-310:** The static Key for ESP-NOW encryption shall be configurable via NVS and not hardcoded in firmware.<br/>
**Rationale:** Allows users to set their own encryption key without needing to modify and reflash firmware, improving security and usability.<br/>
**Alternative considered:** Hardcoded key in firmware — rejected, would require firmware changes to update key and reduce security if firmware is shared. Key configuration via web interface — rejected, adds complexity and requires webserver to be involved in key management, which is not ideal for a common master that should not have project specific logic.

# Boot

## Boot Before Master

**REQ-GEN-400:** Nodes shall handle booting before master is ready — retry ESP-NOW registration until master responds.<br/>
**Rationale:** Nodes may boot before master is ready to receive messages. Retrying registration ensures nodes can come online independently without timing issues.<br/>
**Alternative considered:** Nodes fail if master not ready — rejected, would create boot timing dependencies and reduce reliability.

## Report Firmware to Master

**REQ-GEN-410:** Each ESP shall report its firmware version to master via ESP-NOW at boot.<br/>
**Rationale:** Allows master and webserver to track firmware versions of all nodes, aiding in debugging and ensuring compatibility.<br/>
**Alternative considered:** No firmware version reporting — rejected, would have no visibility into node firmware versions, making debugging and compatibility management more difficult.

# OTA

## Dual Partition Flash

**REQ-GEN-500:** ESPs shall use dual partition flash layout from the start to support OTA.<br/>
**Rationale:** Dual partition is required for OTA updates. Adding it later would require USB reflash of all devices, which is inconvenient once installed in enclosures. Flash space cost is minimal and no hardware changes are needed, so it makes sense to include it from the start.<br/>
**Alternative considered:** Add dual partition later — rejected, defeats the purpose of OTA and would require inconvenient USB reflash of all devices.

## Triggerable via Website/Webserver

**REQ-FW-150:** OTA shall be triggerable per ESP from the Htmx UI on the webserver.<br/>
**Rationale:** Provides a user-friendly way to initiate OTA updates from the web interface.<br/>
**Alternative considered:** OTA only via command line or physical button — rejected, less user-friendly and not suitable for remote updates.

# Performance

## Ticks Rate

**REQ-GEN-600:** FreeRTOS tick rate shall be configured to 1000Hz (1ms tick) via sdkconfig.defaults.<br/>
**Rationale:**: 1ms tick allows for low latency handling of time critical messages (e.g. MIDI note on/off) while keeping CPU overhead manageable. 100Hz tick adds unacceptable latency for time critical messages.<br/>
**Alternative considered:** 100Hz (10ms tick) — rejected, adds unacceptable latency for time critical messages. 1ms tick achieves ~6ms total MIDI note to OSC UDP latency, while 10ms tick adds ~11-20ms.

# Software Organization

## Single VS Project

**REQ-GEN-800:** The project shall use a single VS Code project, including all node code.<br/>
**Rationale:** A single project is easier for development.<br/>
**Alternative considered:** Multiple projects per role — rejected, would increase complexity and reduce maintainability.

## Minimal NVS Writes

**REQ-GEN-820:** NVS write frequency shall be minimized — flash has limited write cycles, NVS wear levelling is enabled.<br/>
**Rationale:** Prevent NVS wear levelling.<br/>
**Alternative considered:** Frequent NVS writes — rejected, would wear out flash memory over time.

## RTOS Tasks

**REQ-MAS-800:** Every ESP shall have the following RTOS tasks: <br/>

- ESP-Now Task (handles incoming messages and sending messages, verifies CRC)
- OTA Task (handles over-the-air updates)
- Node specific task(s)

**Rationale:** Separating concerns into different tasks allows for better organization and responsiveness. ESP-Now task can prioritize handling messages, while OTA and node specific tasks can run independently without blocking message handling.<br/>
**Alternative considered:** Single task for all functionality — rejected, would be less responsive and harder to organize code. No separate task for receiving/sending messages — rejected, would make it harder to prioritize message handling and could lead to dropped messages under load.

## Task Spawning after EPS-NOW Initialization

**REQ-MAS-810:** Every ESP shall spawn tasks after initializing ESP-NOW and peripherals.<br/>
**Rationale:** Ensures ESP-NOW is ready to receive messages as soon as tasks are running, preventing missed messages during startup.<br/>
**Alternative considered:** Spawn tasks before ESP-NOW initialization — rejected, could lead to missed messages during startup if tasks are running before ESP-NOW is ready.

# Testing

# Hardware
