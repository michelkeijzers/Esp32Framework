# OSC Slave

**REQ-OSC-100:** The OSC slave shall receive MIDI messages via ESP-NOW from master.

**REQ-OSC-110:** The OSC slave shall forward MIDI messages as OSC over Wi-Fi UDP to a configurable target IP and port.

**REQ-OSC-120:** The OSC slave shall use dedicated Wi-Fi — separate from the webserver slave.

**REQ-OSC-130:** The OSC slave shall use an FPC external antenna for reliable low-latency Wi-Fi during live performance.

#### MIDI Message Generation

**REQ-GEN-100:** The webserver slave shall generate MIDI messages based on input slave events and stored mappings.

**REQ-GEN-110:** Input-to-MIDI mappings shall be stored in webserver slave NVS and configurable via React UI without reflashing.

**REQ-GEN-120:** The webserver slave shall support configurable MIDI channel, note, velocity, CC value, program change, and transpose per input.

\*\*# Software Organization

# Testing

# Hardware

**REQ-OSC-900:** An ESP32-C3 with U.FL variant with FPC flexible antenna shall be used.<br/>
**Rationale:** To communicate externall, a U.FL antenna is required. FPC adds flexibility for antenna placement and can improve signal strength, especially in enclosures.<br/>
**Alternative considered:** ESP32-C3 with PCB antenna — rejected, would have poor Wi-Fi performance due to antenna being blocked by enclosure or distance from master. ESP32-C3 with U.FL but no FPC — rejected, would limit antenna placement options and could still have performance issues in certain enclosures or placements.
