# STEP 1: MASTER

| Requirement | Prio | Status      | Comment        |
| ----------- | ---- | ----------- | -------------- |
| REQ-GEN-100 | 1    | Implemented |                |
| REQ-GEN-110 | 1    | Implemented |                |
| REQ-GEN-220 | 1    | Implemented |                |
| REQ-GEN-230 | 1    | Implemented |                |
| REQ-GEN-240 | 1    | Implemented |                |
| REQ-GEN-250 | 1    | Later       | Queue overflow |
| REQ-GEN-300 | 1    | Later       | Encryption     |

**REQ-GEN-410:** Each ESP shall report its firmware version to master via ESP-NOW at boot.<br/>
**Rationale:** Allows master and webserver to track firmware versions of all nodes, aiding in debugging and ensuring compatibility.<br/>
**Alternative considered:** No firmware version reporting — rejected, would have no visibility into node firmware versions, making debugging and compatibility management more difficult.

# OTA

**REQ-GEN-500:** ESPs shall use dual partition flash layout from the start to support OTA.<br/>
**Rationale:** Dual partition is required for OTA updates. Adding it later would require USB reflash of all devices, which is inconvenient once installed in enclosures. Flash space cost is minimal and no hardware changes are needed, so it makes sense to include it from the start.<br/>
**Alternative considered:** Add dual partition later — rejected, defeats the purpose of OTA and would require inconvenient USB reflash of all devices.

**REQ-FW-510:** ESPs shall support OTA via temporary Wi-Fi — node temporarily enables Wi-Fi STA mode, connects to router, downloads firmware, reboots, returns to ESP-NOW only mode.<br/>
**Rationale:** Provides a wireless OTA option for nodes that have Wi-Fi capability and are close enough to the router. Allows for OTA without needing physical access for USB reflash.<br/>
**Alternative considered:** OTA only via webservers — rejected, nodes with Wi-Fi capability should be able to update directly without needing to route through the webserver. OTA proxy via ESP-NOW — rejected, adds significant complexity and development effort, and is not strictly necessary for nodes with Wi-Fi capability.

**REQ-FW-150:** OTA shall be triggerable per ESP from the Hemx UI on the webservers.<br/>
**Rationale:** Provides a user-friendly way to initiate OTA updates from the web interface.<br/>
**Alternative considered:** OTA only via command line or physical button — rejected, less user-friendly and not suitable for remote updates.

# Performance

**REQ-GEN-600:** FreeRTOS tick rate shall be configured to 1000Hz (1ms tick) via sdkconfig.defaults.<br/>
**Rationale:**: 1ms tick allows for low latency handling of time critical messages (e.g. MIDI note on/off) while keeping CPU overhead manageable. 100Hz tick adds unacceptable latency for time critical messages.<br/>
**Altarnative considered:** 100Hz (10ms tick) — rejected, adds unacceptable latency for time critical messages. 1ms tick achieves ~6ms total MIDI note to OSC UDP latency, while 10ms tick adds ~11-20ms.

# Software Organization

**REQ-GEN-800:** The project shall use a single VS Code, including all node code.
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

# STEP 2: GPIO NODE

# STEP 3: WEB SERVER

# STEP 4: DISPLAY NODE

# STEP 5: DMX NODE
