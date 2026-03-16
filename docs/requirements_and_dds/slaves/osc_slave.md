# OSC Node

**REQ-OSC-100:** The OSC node shall receive MIDI messages via ESP-NOW from master.

**REQ-OSC-110:** The OSC node shall forward MIDI messages as OSC over Wi-Fi UDP to a configurable target IP and port.

**REQ-OSC-120:** The OSC node shall use dedicated Wi-Fi — separate from the webserver.

**REQ-OSC-130:** The OSC node shall use an FPC external antenna for reliable low-latency Wi-Fi during live performance.

#### MIDI Message Generation

**REQ-GEN-100:** The webserver shall generate MIDI messages based on input node events and stored mappings.

**REQ-GEN-110:** Input-to-MIDI mappings shall be stored in webserver NVS and configurable via Htmx UI without reflashing.

**REQ-GEN-120:** The webserver shall support configurable MIDI channel, note, velocity, CC value, program change, and transpose per input.

# Software Organization

# Testing

# Hardware

**REQ-OSC-900:** An ESP32-C3 with U.FL variant with FPC flexible antenna shall be used.<br/>
**Rationale:** To communicate externall, a U.FL antenna is required. FPC adds flexibility for antenna placement and can improve signal strength, especially in enclosures.<br/>
**Alternative considered:** ESP32-C3 with PCB antenna — rejected, would have poor Wi-Fi performance due to antenna being blocked by enclosure or distance from master. ESP32-C3 with U.FL but no FPC — rejected, would limit antenna placement options and could still have performance issues in certain enclosures or placements.
