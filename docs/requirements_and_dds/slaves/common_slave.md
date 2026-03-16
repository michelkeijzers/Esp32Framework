# COMMON NODE REQUIREMENTS

# Role

## Common Node Role

**REQ-SLV-100:** Node role code shall be fully common between projects — no project specific code, project specific data loaded via NVS at first boot.<br/>
**Rationale:** Node roles are consistent across projects, only data varies per project.<br/>
**Alternative considered:** Per-project node code — rejected, would increase maintenance burden and reduce code reuse.

# Peripherals

## Maximum One UART Peripheral

**REQ-SLV-150:** Each node shall use at most one UART peripheral.<br/>
**Rationale:** Keep one UART available for debugging.<br/>
**Alternative considered:** Multiple UARTs per node — rejected, would consume all UART peripherals and prevent debugging.

## Validate Impossible Hardware Combinations

**REQ-SLV-160:** Compile time validation shall prevent impossible hardware combinations (e.g. two UART features on one node).<br/>
**Rationale:** Prevents invalid configurations that would not function correctly on the hardware.<br/>**Alternative considered:** No compile time validation — rejected, would allow invalid configurations leading to runtime errors.

## Validate Impossible GPIO Budget

**REQ-SLV-170:** Compile time validation shall verify GPIO budget does not exceed 11 available pins.<br/>
**Rationale:** Ensures hardware configurations fit within the physical constraints of the ESP32-C3.<br/>**Alternative considered:** No GPIO budget validation — rejected, would allow configurations that cannot be implemented on the hardware.

# Configuration and NVS

## Owning Domain Data in NVS

**REQ-SLV-200:** Each node shall own its domain data as single source of truth — stored in NVS.<br/>
**Rationale:** Centralizes project specific data in NVS, allowing for configuration without reflashing. Keeps node code common and reusable across projects.<br/>
**Alternative considered:** Hardcoded data in firmware — rejected, would require reflashing for configuration changes and reduce flexibility.

## NVS Structure Identical across Projects

**REQ-SLV-220:** NVS key structure shall be identical across projects — only NVS values differ per project.<br/>
**Rationale:** Allows the same node code to be reused across projects, with only NVS values changing to reflect project specific data.<br/>
**Alternative considered:** Different NVS key structures per project — rejected, would fragment codebase and reduce reusability.

## Version Number for NVS Scheme

**REQ-SLV-250:** Nodes shall have a version number for the NVS scheme.
<br/>**Rationale:** Allows for future changes to the NVS structure while maintaining compatibility with older firmware versions.<br/>
**Alternative considered:** No NVS versioning — rejected, would risk compatibility issues as NVS structure evolves.

# Flashing and OTA

## Notify Master 

**REQ-SLV-300:** Node shall notify master when OTA starts (OTA_START) and completes (OTA_COMPLETE).
**Rationale:** Provides visibility into the OTA process, allowing the master to manage watchdog suppression and monitor update status.<br/>
**Alternative considered:** No notifications for OTA status — rejected, would have no visibility into the update process, complicating monitoring and debugging.

## Dual Partition Flash

**REQ-SLV-305:** All nodes shall use dual partition flash layout from the start to support future OTA.<br/>
**Rationale:** Enables OTA updates without risking bricking devices, as they can roll back to the previous firmware if the new one fails.<br/>
**Alternative considered:** Single partition layout — rejected, would risk bricking devices during OTA updates.

## Report Firmware Version

**REQ-SLV-310:** All nodes shall report their firmware version to master via ESP-NOW at boot.<br/>
**Rationale:** Provides visibility into the firmware versions running on each node, allowing for better monitoring and debugging.<br/>
**Alternative considered:** No firmware version reporting — rejected, would have no visibility into node firmware versions, complicating debugging and maintenance.

## OTA Failure Rollback

**REQ-SLV-320:** All nodes shall roll back automatically to previous firmware on failed boot after OTA.<br/>
**Rationale:** Prevents devices from being bricked by faulty OTA updates, ensuring they can recover and remain functional.<br/>
**Alternative considered:** No automatic rollback — rejected, would risk bricking devices during OTA updates.

## OTA Chunks CRC

**REQ-SLV-350:** OTA proxy shall use CRC16 per chunk — chunk mismatch triggers resend, full binary mismatch triggers abort and rollback.<br/>
**Rationale:** Ensures reliable OTA updates via the proxy, preventing corruption and ensuring devices remain functional.<br/>
**Alternative considered:** No checksums for OTA proxy — rejected, would risk corrupted updates leading to bricked devices.

## OTA Chunk Protocol

**REQ-SLV-360:** OTA proxy chunk transfer shall use per-chunk acknowledgement — sender waits for ACK before sending next chunk, retransmits on timeout.<br/>
**Rationale:** Ensures reliable delivery of OTA chunks, preventing corruption and ensuring devices remain functional.<br/>
**Alternative considered:** No acknowledgements for OTA proxy — rejected, would risk corrupted updates leading to bricked devices.

## OTA Via Website

**REQ-SLV-380:** The webserver shall support triggering OTA updates on any node from the Htmx UI.<br/>
**Rationale:** Provides a user-friendly way to manage OTA updates across all devices from a single interface.<br/>
**Alternative considered:** No UI for OTA updates — rejected, would require manual triggering of updates, reducing usability.

# Boot and Initialization

## First Boot Initialization

## First Boot Data Spreading

## Factory Reset

**REQ-SLV-620:** A factory reset procedure shall exist to wipe NVS and return node to first boot state.<br/>
**Rationale:** Allows users to recover from misconfiguration or prepare devices for a new project without needing special tools or reflashing.<br/>
**Alternative considered:** No factory reset — rejected, would make recovery from misconfiguration difficult and limit reusability of devices across projects.

# Debugging

## Debugging via Webserver

**REQ-SLV-700:** Nodes shall support a debug mode sending debug data via Master to Webserver to Website.<br/>
**Rationale:** Provides a way to get detailed information about node behavior during development and troubleshooting without affecting performance in production.<br/>
**Alternative considered:** No debug mode — rejected, would make development and troubleshooting more difficult.

# Error Handling

## Node Offline Behavior

**REQ-SLV-750:** Node offline behavior during performance shall be defined per node type — system shall degrade gracefully.<br/>
**Rationale:** Ensures that if a node goes offline during performance, the system can continue operating in a degraded mode rather than failing completely.<br/>
**Alternative considered:** No defined offline behaviour — rejected, would lead to unpredictable behavior and potential system failure if a node goes offline during performance.

# Watchdog and Health Monitoring

## Heartbeat

**REQ-SLV-760:** All nodes shall send a heartbeat message to their cluster master every 5 seconds.<br/>
**Rationale:** Allows master to monitor node health and detect offline nodes.<br/>
**Alternative considered:** No heartbeat — rejected, master would have no way to detect offline nodes.

# Performance and Latency

## RTOS Task Prioritization

**REQ-SLV-770:** Time critical routing tasks shall run at highest FreeRTOS priority.<br/>
**Rationale:** Ensures time critical messages are processed with minimal latency, maintaining performance for real-time applications.<br/>
**Alternative considered:** Equal priority for all tasks — rejected, would risk increased latency for time critical

# Software Organization Structure

## Folder per Node Type

**REQ-SLV-800:** Node code shall be organized in subfolders per node type under `software/nodes/`.<br/>
**Rationale:** Keeps code organized and modular, allowing for easier maintenance and development of individual node types.<br/>
**Alternative considered:** Flat structure with all node code in one folder — rejected, would become unwieldy as more node types are added and make it harder to navigate the codebase.

## Shared Common Code

**REQ-SLV-810:** Common code (ESP-NOW, watchdog, messages, NVS helpers) shall be shared across all roles under `software/common/`.<br/>
**Rationale:** Promotes code reuse and reduces duplication, making maintenance easier and ensuring consistency across roles.<br/>
**Alternative considered:** Duplicate code in each role folder — rejected, would increase maintenance burden and risk inconsistencies.

## CMakeLists.txt per Node Type

**REQ-SLV-820:** CMakeLists.txt shall include only source files relevant to the compiled role and node configuration.<br/>
**Rationale:** Keeps firmware size minimal by only including necessary code for the configured role and node type.<br/>
**Alternative considered:** Include all source files regardless of configuration — rejected, would increase firmware size and reduce available flash for NVS and other data.

# Testing

## Node Testing

**REQ-SW-850:** Each node (type) shall be independently testable via unit tests before hardware bring-up.<br/>
**Rationale:** Allows for testing and validation of individual components in isolation, improving code quality and reliability before integrating with hardware.<br/>
**Alternative considered:** No unit tests or only integration tests — rejected, would make it harder to

# Hardware

## ESP32-C3 with No External Antenna

**REQ-SLV-900:** An ESP32-C3 without external FPC or U.FL antenna shall be used (unless overridden by a specific node).
**Rationale:** Only communication with ESP32's in the same enclosure is needed. External antenna is not required and would add unnecessary cost and complexity for most nodes.<br/>
**Alternative considered:** ESP32-C3 with external antenna for all nodes — rejected, would add unnecessary cost and complexity for most nodes, as they do not require external communication.

# Timing and Collision

## Simultaneous Messages

**REQ-SLV-9500:** ESP-NOW simultaneous transmission from multiple nodes shall be handled gracefully — the protocol handles collision at RF level, software queuing handles ordering.
**Rationale:** ESP-NOW is designed to handle simultaneous transmissions, but software should also be designed to queue messages appropriately to ensure reliable communication.<br/>
**Alternative considered:** No handling for simultaneous transmissions — rejected, would lead to unreliable communication and potential message loss during collisions.

