# MASTER REQUIREMENTS

# Message Routing

**REQ-MAS-100:** The master shall maintain a routing table mapping destination MAC addresses to slave roles. This mapping and the MAC addresses will be stored in NVS and is configurable.<br/>
**Rationale:** Allows the master to route messages based on destination MAC address only, keeping it fully generic.<br/>
**Alternative considered:** Dynamic routing table or routing based on message content — rejected, adds complexity and potential for misconfiguration.

**REQ-MAS-105:** The master shall get the MAC addresses via ESP-NOW from the webserver slave at boot and store them in NVS for routing.<br/>
**Rationale:** The webserver slave can have the MAC addresses edited on the Htmx website and still not having the need for uploading firmware to the master because of changed MAC addresses.<br/>
**Alternative considered:** Hardcoded MAC addresses in master code — rejected, would require firmware changes to update MAC addresses and reduce flexibility. Manual entry of MAC addresses via serial or other interface — rejected, less user-friendly and more error-prone than getting them from the webserver slave which has a user-friendly interface for editing them.

**REQ-MAS-110:** The master shall route incoming ESP-NOW messages to their destination MAC address based on the routing table.<br/>
**Rationale:** Ensures messages are delivered to the correct slave based on destination MAC address.<br/>
**Alternative considered:** No routing or routing based on message content — rejected, would limit functionality and require project specific code in master.

**REQ-MAS-120:** The master shall support multi-destination routing for monitoring copies of time critical messages to the webserver slave.<br/>
**Rationale:** Allows the webserver to receive monitoring copies of time critical messages without affecting the main routing path.<br/>
**Alternative considered:** Single-destination routing only — rejected, would prevent monitoring copies and limit webserver functionality.

**REQ-MAS-130:** The master shall support direct routing of time critical messages to their destination without passing through the webserver slave.<br/>
**Rationale:** Ensures time critical messages are delivered with minimal latency.<br/>
**Alternative considered:** All messages via webserver — rejected, latency too high for performance use. Direct routing achieves ~6ms total MIDI note to OSC UDP latency, while routing via webserver adds ~11-20ms.

**REQ-MAS-140:** Master message queue shall have sufficient depth to handle burst traffic without dropping messages — minimum queue depth to be determined during testing.<br/>
**Rationale:** Ensures the master can handle bursts of messages without losing data, maintaining reliability under load.<br/>
**Alternative considered:** Shallow queue with message dropping — rejected, would risk losing important messages during bursts of activity.

# Watch Dog

**REQ-MAS-200:** Master shall apply a grace period at boot during which watchdog alerts are suppressed — all slaves are given time to come online before being considered offline.

**REQ-MAS-210:** The master shall maintain a watchdog for all registered slaves and detect when a slave stops sending heartbeats.<br/>
**Rationale:** Ensures timely detection of offline slaves and allows for appropriate handling.<br/>
**Alternative considered:** No watchdog — rejected, would delay detection of offline slaves and impact system reliability.

**REQ-MAS-220:** The master shall suppress watchdog alerts for a slave during its OTA window.<br/>
**Rationale:** Prevents false offline alerts during OTA updates, allowing the slave time to reboot and come back online.<br/>
**Alternative considered:** No suppression during OTA — rejected, would cause false offline alerts and confusion during updates.

# Logging and Monitoring

**REQ-MAS-300:** The master shall detect when a slave comes back online after being offline and log the event.<br/>
**Rationale:** Provides visibility into slave recovery after outages or updates.<br/>
**Alternative considered:** No detection of recovery — rejected, would have no visibility into slave status changes.

**REQ-MAS-310:** The master shall log all routing events, including message receipt, routing decisions, and slave status changes.<br/>
**Rationale:** Provides a record of system activity for debugging and monitoring purposes.<br/>
**Alternative considered:** No logging — rejected, would make debugging and monitoring difficult.

# Security

**REQ-MAS-400:** The master will manage/spread a changed encryption key to all slaves when the webserver slave sends a new key via ESP-NOW. The following procedure applies:<br/>

- The master sends an UPDATE_SECURITY_KEY message to all slaves with the new key (encrypted with the current key).
- The master waits for a RESPONSE message from each slave confirming the key update.
- Once all slaves have confirmed the key update, the master sends a CHANGE_TO_NEW_SECURITY_KEY message to all slaves, instructing them to start using the new key.
- All slaves that receive the CHANGE_TO_NEW_SECURITY_KEY message send a positive response back and update their key in NVS.
- The master continues sending CHANGE_TO_NEW_SECURITY_KEY until all slaves have responded or a timeout occurs.
- After all slaves have switched (or timeout), the master also updates its key in NVS and begins using the new key.
- In case of a timeout or missing responses, an error is logged.

**Rationale:** Ensures all slaves are updated with the new encryption key without requiring manual updates or firmware changes, improving security and usability.<br/>
**Alternative considered:** Manual update of encryption key on each slave — rejected, would be inconvenient and error-prone, especially for larger deployments. Key configuration via web interface — rejected, adds complexity and requires webserver slave to be involved in key management, which is not ideal for a generic master that should not have project specific logic.

# Software Organization

**REQ-MAS-850:** The master shall have the following RTOS tasks: <br/>

- ESP-Now Task (handles incoming messages, verifies CRC, updates watchdog, routes messages to destination queues)
- Device Management Task (handles slave registration, maintains routing table in NVS, manages watchdog timers)
- Logging Task (handles logging of events)
- OTA Task (handles over-the-air updates)

**Rationale:** Separating concerns into different tasks allows for better organization and responsiveness. ESP-Now task can prioritize handling messages, while other tasks can run independently without blocking message handling.<br/>
**Alternative considered:** Single task for all functionality — rejected, would be less responsive and harder to organize code. No separate task for receiving/sending messages — rejected, would make it harder to prioritize message handling and could lead to dropped messages under load.

# Testing

# Hardware

# MESSAGES

**Message ID: REGISTER**<br/>
**Description:** Sent by slave to master at boot to register itself and its role. Contains slave role and any relevant metadata (e.g. firmware version).<br/>
**Direction:** Slave to Master<br/>
**Parameters:**<br/>

- Generic parameters: (these will be omitted in further messages)
  - Version Number (uint8_t)
  - Sequence Number (uint8_t)
  - Destination Role (Remote, Slave), (uint8_t/enum)
  - Destination Slave type (GPIO, Webserver, Display, etc.), (uint8_t/enum)
  - Destination Slave Index (for multiple slaves of same type, e.g. GPIO slave 1 vs GPIO slave 2), (uint8_t)
  - CRC16 Checksum (uint16_t)

- Message specific parameters:
  - Role (Remote, Slave), (uint8_t/enum)
  - Slave Type (GPIO, Webserver, Display, etc.), (uint8_t/enum)
  - Slave Index (for multiple slaves of same type, e.g. GPIO slave 1 vs GPIO slave 2), (uint8_t)
  - Firmware Version (e.g. 3.1.0) (uint8_t for major_release, minor_release, patch)

**Message ID: UPDATE_SECURITY_KEY**<br/>
**Specific Parameters:**<br/>

- Security key (uint8[16], 16 bytes)

**Message ID: CHANGE_TO_NEW_SECURITY_KEY**<br/>
**Description:** Sent by master to slaves to notify them of a new security key after receiving a new key from the webserver slave.<br/>
**Direction:** Master to Slaves<br/>
**Specific Parameters:** None<br/>

**Message ID: RESPONSE**<br/>
**Description:** Sent by slave to master at boot to register itself and its role. Contains slave role and any relevant metadata (e.g. firmware version).<br/>
**Direction:** Both <br/>
**Specific Parameters:**:

- Result (0 = OK, 1..255 = error code), (uint8_t)

**Message ID: HEARTBEAT**<br/>
**Description:** Sent periodically by slave to master to indicate it is still online.
**Direction:** Slave to Master<br/>
**Specific Parameters:** None (only generic parameters)

**Message ID: ERROR**<br/>
**Description:** Sent by slave to master when an error occurs that the master should be aware of (e.g. failed sensor reading, failed actuation, etc.).<br/>
**Direction:** Slave to Master<br/>
**Specific Parameters:**:
