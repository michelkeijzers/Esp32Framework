# WEBSERVER SLAVE

# Role

**REQ-WEB-100:** The webserver slave shall be the only role rewritten per project.<br/>
**Rationale:** Webserver slave handles project specific logic and UI — requires customization per project.<br/>
**Alternative considered:** Generic webserver slave — rejected, would limit project specific functionality.

**REQ-WEB-110:** The webserver slave shall be the brain of the system — owning all project logic, mappings, and orchestration.<br/>
**Rationale:** Centralizes project specific logic in one role, simplifies maintenance and development.<br/>
**Alternative considered:** Distributed logic across slaves — rejected, would increase complexity and coupling between slaves.

**REQ-WEB-120:** The webserver slave shall NOT perform message routing — routing is handled exclusively by the master.<br/>
**Rationale:** Keeps separation of concerns clear — master handles routing, webserver handles project logic and UI.<br/>
**Alternative considered:** Webserver performs routing decisions — rejected, would blur separation of concerns and require project specific code in master.

# Security

**REQ-SEC-110:** Webserver authentication is not enabled by default — deferred, acceptable for hobby use.<br/>
**Rationale:** Authentication adds complexity and is not strictly necessary for hobby use. Can be added in the future if needed.<br/>
**Alternative considered:** Authentication via login.

## React Website

**REQ-WEB-200:** The webserver slave shall serve a React bundle from LittleFS.<br/>
**Rationale:** Provides a modern, responsive UI for configuration and monitoring.<br/>
**Alternative considered:** No webserver or simpler UI — rejected, would limit usability and configuration options.

## WiFi Connection

**REQ-WEB-300:** The webserver slave shall attempt router connection (STA mode) at boot and fall back to own AP (192.168.4.1) if no router is available.<br/>
**Rationale:** Allows for flexible deployment — can connect to existing Wi-Fi or create its own network for direct connection.<br/>
**Alternative considered:** AP only or STA only — rejected, would limit deployment options.

# OTA Updates

**REQ-WEB-400:** OTA updates shall only be available on the webserver slave when connected to a router in STA mode.<br/>
**Rationale:** OTA via Wi-Fi requires a stable connection to a router. Webserver slave is the only role with Wi-Fi capability, so it is the only candidate for OTA updates.<br/>
**Alternative considered:** OTA on all slaves — rejected, slaves without Wi-Fi cannot support OTA, would require additional hardware or complex OTA proxy solution.

# Performance

**REQ-WEB-500:** Webserver tasks shall run at lower FreeRTOS priority than routing tasks.<br/>
**Rationale:** Ensures webserver processing does not interfere with time critical message routing handled by the master.<br/>
**Alternative considered:** Webserver tasks at same or higher priority than routing tasks — rejected, could cause latency in time critical message handling, impacting performance.

# Error Handling

**REQ-WEB-600:** Webserver slave losing Wi-Fi shall not affect ESP-NOW routing — master and slaves continue operating normally.

# Software Organization

# Testing

# Hardware

**REQ-WEB-900:** An ESP32-C3 with U.FL variant with FPC flexible antenna shall be used.<br/>
**Rationale:** To communicate externally, a U.FL antenna is required. FPC adds flexibility for antenna placement and can improve signal strength, especially in enclosures.<br/>
**Alternative considered:** ESP32-C3 with PCB antenna — rejected, would have poor Wi-Fi performance due to antenna being blocked by enclosure or distance from master. ESP32-C3 with U.FL but no FPC — rejected, would limit antenna placement options and could still have performance issues in certain enclosures or placements.
