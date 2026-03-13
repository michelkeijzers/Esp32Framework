# WEBSERVER SLAVE

# Role

## Rewritten Role

**REQ-WEB-100:** The webserver slave shall be the only role rewritten per project.<br/>
**Rationale:** Webserver slave handles project specific logic and UI — requires customization per project.<br/>
**Alternative considered:** Generic webserver slave — rejected, would limit project specific functionality.

## Brains

**REQ-WEB-110:** The webserver slave shall be the brain of the system — owning all project logic, mappings, and orchestration.<br/>
**Rationale:** Centralizes project specific logic in one role, simplifies maintenance and development.<br/>
**Alternative considered:** Distributed logic across slaves — rejected, would increase complexity and coupling between slaves.

## MAC Addresses

**REQ-WEB-120:** The webserver slave shall send the MAC addresses to the master via ESP-NOW at boot for routing purposes.<br/>
**Rationale:** Ensures the master has the correct MAC addresses for routing without requiring manual configuration or firmware updates.<br/>
**Alternative considered:** Hardcoded MAC addresses in master code — rejected, would require firmware changes to update MAC addresses and reduce flexibility. Manual entry of MAC addresses via serial or other interface — rejected, less user-friendly and more error-prone than getting them from the webserver slave which has a user-friendly interface for editing them.

# Platform 

## HTMX on LittleFS

**REQ-WEB-200:** The webserver slave shall serve a Htmx bundle from LittleFS.<br/>
**Rationale:** Provides a modern, responsive UI for configuration and monitoring.<br/>
**Alternative considered:** No webserver or simpler UI — rejected, would limit usability and configuration options.

## Pico.css

**REQ-WEB-200:** The webserver slave use pico.css for CSS styling.<br/>
**Rationale:** Lightweight, modern CSS framework that provides a clean and responsive design with minimal effort.<br/>
**Alternative considered:** Custom CSS or heavier frameworks like Bootstrap — rejected, would require more development time and increase resource usage without significant benefits for this application.

# WiFi Connection

## STA+AP Mode

**REQ-WEB-250:** The webserver slave shall attempt router connection (STA+AP mode, Station + Access Point Mode) at boot and fall back to own AP (192.168.4.1) if no router is available.<br/>
**Rationale:** Allows for flexible deployment — can connect to existing Wi-Fi or create its own network for direct connection.<br/>
**Alternative considered:** AP only or STA only — rejected, would limit deployment options.

## SSE Messages

**REQ-WEB-260: ** The webserver slave shall send status updates to the website via Server-Sent Events (SSE) for real-time monitoring and stop sending SSE messages when the connection is lost with the SSE client (browser).<br/>
**Rationale:** Provides real-time updates to the user interface without requiring manual refreshes, improving user experience and allowing for timely monitoring of system status.<br/>
**Alternative considered:** Polling from the frontend — rejected, less efficient and less real-time than SSE.

# Security

## Authentication 

**REQ-SEC-600:** Webserver authentication is not enabled by default — deferred, acceptable for hobby use.<br/>
**Rationale:** Authentication adds complexity and is not strictly necessary for hobby use. Can be added in the future if needed.<br/>
**Alternative considered:** Authentication via login.

## ESP-NOW Key

**REQ-SEC-610:** Webserver shall provide a means to change the static security key and able to message it to the master to spread.<br/>
**Rationale:** Allows users to set their own encryption key without needing to modify and reflash firmware, improving security and usability.<br/>
**Alternative considered:** Hardcoded key in firmware — rejected, would require firmware changes to update key and reduce security if firmware is shared. Key configuration via web interface — rejected, adds complexity and requires webserver slave to be involved in key management, which is not ideal for a generic master that should not have project specific logic.

## Wi-Fi Security

**REQ-SEC-620:** The webserver slave shall support WPA2 security. Also a scrambled password can be received from the website and used. HTTPS will not be used.<br/>
**Rationale:** WPA2 is a widely supported and secure Wi-Fi security protocol. Scrambled password allows for secure transmission of Wi-Fi credentials without needing to implement HTTPS, which can be complex and resource-intensive on an embedded device.<br/>
**Alternative considered:** Open Wi-Fi (no security) — rejected, would be a security risk. HTTPS — rejected, adds complexity and resource usage that may not be justified for this application.

# OTA Updates

## Wi-Fi OTA

**REQ-WEB-650:** OTA updates shall only be available on the webserver slave when connected to a router in STA mode. The firmware will be transported in chunks with retries handled by the website.<br/>
**Rationale:** OTA via Wi-Fi requires a stable connection to a router. Webserver slave is the only role with Wi-Fi capability, so it is the only candidate for OTA updates.<br/>
**Alternative considered:** OTA on all slaves — rejected, slaves without Wi-Fi cannot support OTA, would require additional hardware or complex OTA proxy solution.

**REQ-WEB-660:** OTA updates for other nodes will be managed by the webserver slave via the master.
**Rationale:** Centralizes OTA management in the webserver slave, which has the user interface and can communicate with the master to coordinate updates across all nodes.<br/>
**Alternative considered:** Direct OTA from master or other slaves — rejected, would require all nodes to have Wi-Fi capability and OTA logic, increasing complexity and resource usage on non-webserver slaves.

# Performance

## RTOS Priority

**REQ-WEB-700:** Webserver tasks shall run at lower FreeRTOS priority than routing tasks.<br/>
**Rationale:** Ensures webserver processing does not interfere with time critical message routing handled by the master.<br/>
**Alternative considered:** Webserver tasks at same or higher priority than routing tasks — rejected, could cause latency in time critical message handling, impacting performance.

# Error Handling

## Wi-Fi Loss

**REQ-WEB-750:** Webserver slave losing Wi-Fi shall not affect ESP-NOW routing — master and slaves continue operating normally.<br/>
**Rationale:** Wi-Fi connectivity is not critical for core system functionality, which relies on ESP-NOW. The system should be resilient to Wi-Fi issues without impacting overall operation.<br/>
**Alternative considered:** Wi-Fi loss causes system instability or failure — rejected, would reduce reliability and user experience.

# Software Organization

# Testing

# Hardware

## U.FL with FPC Antenna

**REQ-WEB-900:** An ESP32-C3 with U.FL variant with FPC flexible antenna shall be used.<br/>
**Rationale:** To communicate externally, a U.FL antenna is required. FPC adds flexibility for antenna placement and can improve signal strength, especially in enclosures.<br/>
**Alternative considered:** ESP32-C3 with PCB antenna — rejected, would have poor Wi-Fi performance due to antenna being blocked by enclosure or distance from master. ESP32-C3 with U.FL but no FPC — rejected, would limit antenna placement options and could still have performance issues in certain enclosures or placements.
