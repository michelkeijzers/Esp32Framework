# GENERIC SLAVE REQUIREMENTS

# Role

**REQ-SLV-100:** Slave role code shall be fully generic — no project specific code, project specific data loaded via NVS at first boot.<br/>
**Rationale:** Slave roles are consistent across projects, only data varies per project.<br/>
**Alternative considered:** Per-project slave code — rejected, would increase maintenance burden and reduce code reuse.

# Peripherals

**REQ-SLV-150:** Each slave shall use at most one UART peripheral.<br/>
**Rationale:** Keep one UART available for debugging.<br/>
**Alternative considered:** Multiple UARTs per slave — rejected, would consume all UART peripherals and prevent debugging.

**REQ-SLV-160:** Compile time validation shall prevent impossible hardware combinations (e.g. two UART features on one slave).<br/>
**Rationale:** Prevents invalid configurations that would not function correctly on the hardware.<br/>**Alternative considered:** No compile time validation — rejected, would allow invalid configurations leading to runtime errors.

**REQ-SLV-170:** Compile time validation shall verify GPIO budget does not exceed 11 available pins.<br/>
**Rationale:** Ensures hardware configurations fit within the physical constraints of the ESP32-C3.<br/>**Alternative considered:** No GPIO budget validation — rejected, would allow configurations that cannot be implemented on the hardware.

# Configuration and NVS

**REQ-SLV-200:** Each slave shall own its domain data as single source of truth — stored in NVS.<br/>
**Rationale:** Centralizes project specific data in NVS, allowing for configuration without reflashing. Keeps slave code generic and reusable across projects.<br/>
**Alternative considered:** Hardcoded data in firmware — rejected, would require reflashing for configuration changes and reduce flexibility.

**REQ-SLV-220:** NVS key structure shall be identical across projects — only NVS values differ per project.<br/>
**Rationale:** Allows the same slave code to be reused across projects, with only NVS values changing to reflect project specific data.<br/>
**Alternative considered:** Different NVS key structures per project — rejected, would fragment codebase and reduce reusability.

**REQ-SLV-230:** The webserver slave shall load project specific NVS data onto each slave at first boot.<br/>
**Rationale:** Ensures slaves are initialized with the correct project specific data without requiring manual configuration or reflashing.<br/>
**Alternative considered:** Manual NVS configuration or hardcoded data — rejected, would reduce usability and flexibility.

**REQ-SLV-240:** A factory reset procedure shall exist to wipe NVS and return slave to first boot state.<br/>
**Rationale:** Allows users to recover from misconfiguration or prepare devices for a new project without needing special tools or reflashing.<br/>
**Alternative considered:** No factory reset — rejected, would make recovery from misconfiguration difficult and limit reusability of devices across projects.

**REQ-SLV-250:** Slaves shall have a version number for the NVS scheme.
<br/>**Rationale:** Allows for future changes to the NVS structure while maintaining compatibility with older firmware versions.<br/>
**Alternative considered:** No NVS versioning — rejected, would risk compatibility issues as NVS structure evolves.

# Flashing and OTA

**REQ-SLV-300:** Slave shall notify master when OTA starts (OTA_START) and completes (OTA_COMPLETE).
**Rationale:** Provides visibility into the OTA process, allowing the master to manage watchdog suppression and monitor update status.<br/>
**Alternative considered:** No notifications for OTA status — rejected, would have no visibility into the update process, complicating monitoring and debugging.

**REQ-SLV-305:** All slaves shall use dual partition flash layout from the start to support future OTA.<br/>
**Rationale:** Enables OTA updates without risking bricking devices, as they can roll back to the previous firmware if the new one fails.<br/>
**Alternative considered:** Single partition layout — rejected, would risk bricking devices during OTA updates.

**REQ-SLV-310:** All slaves shall store router SSID and password in NVS for temporary Wi-Fi OTA.
**Rationale:** Allows slaves to connect to Wi-Fi for OTA updates when needed, without requiring hardcoded credentials or manual configuration each time.<br/>
**Alternative considered:** No Wi-Fi credentials stored on slaves — rejected, would prevent OTA updates on slaves without Wi-Fi capability, or require manual configuration for each update.

**REQ-SLV-315:** All slaves shall report their firmware version to master via ESP-NOW at boot.<br/>
**Rationale:** Provides visibility into the firmware versions running on each slave, allowing for better monitoring and debugging.<br/>
**Alternative considered:** No firmware version reporting — rejected, would have no visibility into slave firmware versions, complicating debugging and maintenance.

**REQ-SLV-320:** All slaves shall roll back automatically to previous firmware on failed boot after OTA.<br/>
**Rationale:** Prevents devices from being bricked by faulty OTA updates, ensuring they can recover and remain functional.<br/>
**Alternative considered:** No automatic rollback — rejected, would risk bricking devices during OTA updates.

**REQ-SLV-330:** Slaves shall support OTA via temporary Wi-Fi — slave temporarily enables Wi-Fi STA mode, connects to router, downloads firmware, reboots, returns to ESP-NOW only mode.<br/>
**Rationale:** Allows slaves without permanent Wi-Fi capability to receive OTA updates when needed, increasing flexibility and maintainability.<br/>
**Alternative considered:** No OTA on slaves without Wi-Fi — rejected, would prevent updates and improvements on those devices, or require physical access for updates.

**REQ-SLV-340:** OTA proxy via webserver + ESP-NOW shall be implemented as a deferred feature — webserver downloads firmware via Wi-Fi and pushes to slave via ESP-NOW chunks, no Wi-Fi required on slave.<br/>
**Rationale:** Provides a way to update slaves without Wi-Fi capability, increasing flexibility and maintainability. Deferred implementation allows focus on core features first.<br/>
**Alternative considered:** No OTA proxy — rejected, would prevent updates on slaves without Wi-Fi, or require physical access for updates.

**REQ-SLV-350:** OTA proxy shall use CRC16 per chunk and CRC32 over the full binary — chunk mismatch triggers resend, full binary mismatch triggers abort and rollback.<br/>
**Rationale:** Ensures reliable OTA updates via the proxy, preventing corruption and ensuring devices remain functional.<br/>
**Alternative considered:** No checksums for OTA proxy — rejected, would risk corrupted updates leading to bricked devices.

**REQ-SLV-360:** OTA proxy chunk transfer shall use per-chunk acknowledgement — sender waits for ACK before sending next chunk, retransmits on timeout.<br/>
**Rationale:** Ensures reliable delivery of OTA chunks, preventing corruption and ensuring devices remain functional.<br/>
**Alternative considered:** No acknowledgements for OTA proxy — rejected, would risk corrupted updates leading to bricked devices.

**REQ-SLV-370:** All slaves shall support OTA via the proxy method, even those with Wi-Fi capability — allows for a single OTA method across all devices, simplifying the update process.<br/>
**Rationale:** Provides a consistent OTA method for all devices, regardless of Wi-Fi capability, increasing flexibility and maintainability.<br/>
**Alternative considered:** OTA via Wi-Fi for capable devices and proxy for non-Wi-Fi devices — rejected, would create multiple update methods and increase complexity.

**REQ-SLV-380:** The webserver slave shall support triggering OTA updates on any slave from the React UI.<br/>
**Rationale:** Provides a user-friendly way to manage OTA updates across all devices from a single interface.<br/>
**Alternative considered:** No UI for OTA updates — rejected, would require manual triggering of updates, reducing usability.

**REQ-SLV-390:** Slaves shall notify master when OTA starts (MSG_OTA_STARTED) and completes (MSG_OTA_COMPLETE) via ESP-NOW messages.<br/>
**Rationale:** Provides visibility into the OTA process, allowing the master to manage watchdog suppression and monitor update status.<br/>
**Alternative considered:** No notifications for OTA status — rejected, would have no visibility into the update process, complicating monitoring and debugging.

# Boot and Initialization

**REQ-SLV-400:** Slaves shall handle booting before master is ready — retry ESP-NOW registration until master responds.<br/>
**Rationale:** Ensures slaves can come online in any order without causing issues, allowing for flexible deployment and recovery.<br/>
**Alternative considered:** Slaves require master to be online at boot — rejected, would create boot order dependencies and potential issues during recovery or deployment.

**REQ-SLV-610:** Slaves shall detect first boot (empty NVS) and request initialization data from webserver slave.<br/>
**Rationale:** Automates the initial configuration of slaves, ensuring they receive the necessary project specific data without manual intervention.<br/>
**Alternative considered:** Manual initialization or hardcoded defaults — rejected, would reduce usability and flexibility.

**REQ-SLV-620:** A factory reset procedure shall exist to wipe NVS and return slave to first boot state.<br/>
**Rationale:** Allows users to recover from misconfiguration or prepare devices for a new project without needing special tools or reflashing.<br/>
**Alternative considered:** No factory reset — rejected, would make recovery from misconfiguration difficult and limit reusability of devices across projects.

# Debugging

**REQ-SLV-700:** Slaves shall support a debug mode enabled that outputs detailed logs over UART for development and troubleshooting purposes.<br/>
**Rationale:** Provides a way to get detailed information about slave behavior during development and troubleshooting without affecting performance in production.<br/>
**Alternative considered:** No debug mode — rejected, would make development and troubleshooting more difficult.

# Error Handling

**REQ-SLV-750:** Slave offline behaviour during performance shall be defined per slave type — system shall degrade gracefully.<br/>
**Rationale:** Ensures that if a slave goes offline during performance, the system can continue operating in a degraded mode rather than failing completely.<br/>
**Alternative considered:** No defined offline behaviour — rejected, would lead to unpredictable behavior and potential system failure if a slave goes offline during performance.

# Watchdog and Health Monitoring

**REQ-SLV-760:** All slaves shall send a heartbeat message to their cluster master every 5 seconds.<br/>
**Rationale:** Allows master to monitor slave health and detect offline nodes.<br/>
**Alternative considered:** No heartbeat — rejected, master would have no way to detect offline slaves.

# Performance and Latency

**REQ-SLV-770:** Time critical routing tasks shall run at highest FreeRTOS priority.<br/>
**Rationale:** Ensures time critical messages are processed with minimal latency, maintaining performance for real-time applications.<br/>
**Alternative considered:** Equal priority for all tasks — rejected, would risk increased latency for time critical

**REQ-SLV-780:** Monitoring copies of time critical messages sent to the webserver slave shall never block the time critical routing path.<br/>
**Rationale:** Ensures that monitoring does not interfere with the main routing path, maintaining performance for time critical messages.<br/>
**Alternative considered:** Monitoring copies sent via the same queue as the main routing path — rejected, would risk increased latency for time critical messages when monitoring is enabled.

\*\*# Software Organization Structure

**REQ-SLV-800:** Slave code shall be organized in subfolders per slave type under `software/slaves/`.<br/>
**Rationale:** Keeps code organized and modular, allowing for easier maintenance and development of individual slave types.<br/>
**Alternative considered:** Flat structure with all slave code in one folder — rejected, would become unwieldy as more slave types are added and make it harder to navigate the codebase.

**REQ-SLV-810:** Common code (ESP-NOW, watchdog, messages, NVS helpers) shall be shared across all roles under `software/common/`.<br/>
**Rationale:** Promotes code reuse and reduces duplication, making maintenance easier and ensuring consistency across roles.<br/>
**Alternative considered:** Duplicate code in each role folder — rejected, would increase maintenance burden and risk inconsistencies.

**REQ-SLV-820:** CMakeLists.txt shall include only source files relevant to the compiled role and slave configuration.<br/>
**Rationale:** Keeps firmware size minimal by only including necessary code for the configured role and slave type.<br/>
**Alternative considered:** Include all source files regardless of configuration — rejected, would increase firmware size and reduce available flash for NVS and other data.

**REQ-SW-830:** Each component shall be independently testable via unit tests before hardware bring-up.<br/>
**Rationale:** Allows for testing and validation of individual components in isolation, improving code quality and reliability before integrating with hardware.<br/>
**Alternative considered:** No unit tests or only integration tests — rejected, would make it harder to

# Testing

# Hardware

**REQ-SLV-900:** An ESP32-C3 without external FPC or U.FL antenna shall be used (unless overridden by a specific slave).
**Rationale:** Only communication with ESP32's in the same enclosure is needed. External antenna is not required and would add unnecessary cost and complexity for most slaves.<br/>
**Alternative considered:** ESP32-C3 with external antenna for all slaves — rejected, would add unnecessary cost and complexity for most slaves, as they do not require external communication.

**REQ-NVS-120:** A backup and restore procedure for NVS data shall be defined — deferred.

### Timing and Collision

**REQ-TIM-100:** ESP-NOW simultaneous transmission from multiple slaves shall be handled gracefully — the protocol handles collision at RF level, software queuing handles ordering.

**REQ-TIM-110:** Master receive queue depth shall be defined and documented — minimum size determined during testing.

**REQ-TIM-120:** Queue overflow drop strategy shall be defined per queue — drop oldest or drop newest.
