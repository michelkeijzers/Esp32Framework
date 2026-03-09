# GENERIC REQUIREMENTS AND DESIGN DECISIONS

# Roles

**REQ-GEN-100:** The system shall support four roles: ROLE_MASTER, ROLE_REMOTE, ROLE_WEBSERVER, ROLE_SLAVE.<br/>
**Rationale:** Defines the different roles each ESP can assume in the system.<br/>
**Alternative considered:** Fewer or more roles — rejected, would limit flexibility or add unnecessary complexity.

**REQ-GEN-110:** The role of each ESP shall be determined at compile time via configuration / NVS. No runtime role switching.<br/>
**Rationale:** Roles are static per project — no need for dynamic switching. Compile time configuration simplifies implementation and reduces attack surface.<br/>
**Alternative considered:** Runtime role switching — rejected, adds complexity and potential for misconfiguration.

**REQ-GEN-120:** Master and remote role code shall be fully generic — no project specific code, never reflashed between projects.<br/>
**Rationale:** Master is a blind router, remote is a simple heartbeat sender — both roles are generic across projects and do not require project specific logic.<br/>
**Alternative considered:** Per-project master and remote code — rejected, would fragment codebase and lose reusability.

# ESP-NOW Protocol

**REQ-GEN-200:** ESP-NOW shall be used for all inter-ESP communication — no Wi-Fi or Bluetooth connections between ESPs.
**Rationale:** ESP-NOW provides low-latency, connectionless communication ideal for real-time performance use. Avoids Wi-Fi overhead and complexity.<br/>
**Alternative considered:** Wi-Fi or Bluetooth — rejected, higher latency and complexity, not suitable for real-time performance.

**REQ-GEN-210:** Maximum ESP-NOW message payload shall not exceed 250 bytes — hard protocol limit.<br/>
**Rationale:** ESP-NOW has a maximum payload size of 250 bytes. Messages must be designed to fit within this limit.<br/>
**Alternative considered:** Larger messages with fragmentation — rejected, adds complexity and latency.

**REQ-GEN-220:** All ESP-NOW messages shall include a sequence number to detect lost or duplicate messages.<br/>
**Rationale:** ESP-NOW does not guarantee delivery or ordering. Sequence numbers allow receivers to detect and handle lost or duplicate messages appropriately.<br/>
**Alternative considered:** No sequence numbers — rejected, would have no way to detect lost or duplicate messages, impacting reliability.

**REQ-GEN-230:** All ESP-NOW messages shall include a version field to support future firmware compatibility.<br/>
**Rationale:** Allows for future firmware updates on individual slaves without breaking message compatibility with other slaves on different firmware versions.<br/>
**Alternative considered:** No version field — rejected, would risk compatibility issues as firmware evolves.

**REQ-GEN-240:** All ESP-NOW messages shall include a CRC16 checksum calculated over the full message including payload — corrupted messages shall be silently discarded.<br/>
**Rationale:** ESP-NOW transmission can corrupt data — silent corruption is worse than a dropped message. CRC16 allows receivers to detect corrupted messages and discard them without processing invalid data.<br/>
**Alternative considered:** No CRC — rejected, would risk silent data corruption leading to unpredictable behavior.

**REQ-GEN-250:** Queue overflow strategy shall be defined — drop oldest or drop newest — and documented per queue.<br/>
**Rationale:** In high traffic scenarios, queues may become full. A defined strategy for handling overflow ensures predictable behavior under load.<br/>
**Alternative considered:** No defined strategy — rejected, would lead to unpredictable behavior when queues are full.

# Security

**REQ-SEC-300:** ESP-NOW static Key encryption shall be used.<br/>
**Rationale:** ESP-NOW messages are transmitted over the air and can be intercepted. Static Key encryption provides a basic level of security to prevent unauthorized interception and tampering of messages.<br/>
**Alternative considered:** No encryption — rejected, would leave messages vulnerable to interception and tampering. Dynamic keys or more advanced encryption — rejected, adds complexity and is not strictly necessary for hobby use. Key management can be handled securely via NVS and physical access to devices. Obfuscation of key in code can provide additional security through obscurity, but no private data is sent. Application-Level security (magic number in message) is not as good as static keys.

# Boot

**REQ-GEN-400:** Slaves shall handle booting before master is ready — retry ESP-NOW registration until master responds.<br/>
**Rationale:** Slaves may boot before master is ready to receive messages. Retrying registration ensures slaves can come online independently without timing issues.<br/>
**Alternative considered:** Slaves fail if master not ready — rejected, would create boot timing dependencies and reduce reliability.

**REQ-GEN-410:** Each ESP shall report its firmware version to master via ESP-NOW at boot.<br/>
**Rationale:** Allows master and webserver to track firmware versions of all slaves, aiding in debugging and ensuring compatibility.<br/>
**Alternative considered:** No firmware version reporting — rejected, would have no visibility into slave firmware versions, making debugging and compatibility management more difficult.

# OTA

**REQ-GEN-500:** ESPs shall use dual partition flash layout from the start to support OTA.<br/>
**Rationale:** Dual partition is required for OTA updates. Adding it later would require USB reflash of all devices, which is inconvenient once installed in enclosures. Flash space cost is minimal and no hardware changes are needed, so it makes sense to include it from the start.<br/>
**Alternative considered:** Add dual partition later — rejected, defeats the purpose of OTA and would require inconvenient USB reflash of all devices.

**REQ-FW-510:** ESPs shall support OTA via temporary Wi-Fi — slave temporarily enables Wi-Fi STA mode, connects to router, downloads firmware, reboots, returns to ESP-NOW only mode.<br/>
**Rationale:** Provides a wireless OTA option for slaves that have Wi-Fi capability and are close enough to the router. Allows for OTA without needing physical access for USB reflash.<br/>
**Alternative considered:** OTA only via webserver slave — rejected, slaves with Wi-Fi capability should be able to update directly without needing to route through the webserver. OTA proxy via ESP-NOW — rejected, adds significant complexity and development effort, and is not strictly necessary for slaves with Wi-Fi capability.

**REQ-FW-150:** OTA shall be triggerable per ESP from the React UI on the webserver slave.<br/>
**Rationale:** Provides a user-friendly way to initiate OTA updates from the web interface.<br/>
**Alternative considered:** OTA only via command line or physical button — rejected, less user-friendly and not suitable for remote updates.

# Performance

**REQ-GEN-600:** FreeRTOS tick rate shall be configured to 1000Hz (1ms tick) via sdkconfig.defaults.<br/>
**Rationale:**: 1ms tick allows for low latency handling of time critical messages (e.g. MIDI note on/off) while keeping CPU overhead manageable. 100Hz tick adds unacceptable latency for time critical messages.<br/>
**Altarnative considered:** 100Hz (10ms tick) — rejected, adds unacceptable latency for time critical messages. 1ms tick achieves ~6ms total MIDI note to OSC UDP latency, while 10ms tick adds ~11-20ms.

\*\*# Software Organization

**REQ-GEN-800:** The project shall use a single VS Code, including all slave code.
**Rationale:** A single project is easier for development.
**Alternative considered:** Multiple projects per role — rejected, would increase complexity and reduce maintainability.

**REQ-GEN-810:** The project shall use a single ESP-IDF project with role selection via configuration/NVS.<br/>
**Rationale:** A single project with role selection simplifies development and maintenance, as all code is in one place and can be reused across roles. Role-specific code can be conditionally compiled or executed based on the selected role, allowing for maximum code reuse while still supporting different functionality per role.<br/>
**Alternative considered:** Separate ESP-IDF projects per role — rejected, would fragment codebase and reduce reusability, as common code would need to be duplicated across projects.

**REQ-GEN-820:** NVS write frequency shall be minimized — flash has limited write cycles, NVS wear levelling is enabled.<br/>
**Rationale:** Prevent NVS wear levelling.
**Alternative considered:** Frequent NVS writes — rejected, would wear out flash memory over time.

# Testing

# Hardware
