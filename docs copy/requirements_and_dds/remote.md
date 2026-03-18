# REMOTE REQUIREMENTS

# Role

**REQ-REM-100:** The remote role shall send a heartbeat to the main cluster master.<br/>
**Rationale:** Allows the remote to be monitored by the master, ensuring it is online and functioning.<br/>
**Alternative considered:** Remote does not send heartbeat — rejected, master would have no way to detect if remote is online.

# Hardware

**REQ-REM-900:** An ESP32-C3 with U.FL variant with FPC flexible antenna shall be used.<br/>
**Rationale:** To communicate externall, a U.FL antenna is required. FPC adds flexibility for antenna placement and can improve signal strength, especially in enclosures.<br/>
**Alternative considered:** ESP32-C3 with PCB antenna — rejected, would have poor Wi-Fi performance due to antenna being blocked by enclosure or distance from master. ESP32-C3 with U.FL but no FPC — rejected, would limit antenna placement options and could still have performance issues in certain enclosures or placements.
