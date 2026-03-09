# MASTER REQUIREMENTS

# Message Routing

**REQ-MAS-100:** The master shall maintain a routing table mapping destination MAC addresses to slave roles. This mapping and the MAC addresses will be stored in NVS and is configurable.<br/>
**Rationale:** Allows the master to route messages based on destination MAC address only, keeping it fully generic.<br/>
**Alternative considered:** Dynamic routing table or routing based on message content — rejected, adds complexity and potential for misconfiguration.

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

\*\*# Software Organization

# Testing

# Hardware
