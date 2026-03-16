# MIDI NODE

**REQ-MIDI-100:** The MIDI node shall support MIDI IN via 6N138 optocoupler with galvanic isolation.

**REQ-MIDI-110:** The MIDI node shall support MIDI OUT via DIN-5 connector.

**REQ-MIDI-120:** The MIDI node shall support MIDI merge — combining external MIDI IN with internally generated MIDI messages received via ESP-NOW.

**REQ-MIDI-130:** The MIDI merge buffer shall handle simultaneous messages from both sources without corrupting either stream.

**REQ-MIDI-140:** The MIDI node shall store patch data (channel, program number) in NVS.

**REQ-MIDI-150:** The MIDI node shall forward merged MIDI stream to both MIDI OUT and OSC node.

**REQ-PERF-130:** MIDI note messages shall be routed directly from MIDI node to OSC node — bypassing the webserver entirely.

**REQ-PERF-140:** Total MIDI note to OSC UDP latency shall not exceed 10ms under normal conditions.

**REQ-ERR-120:** MIDI merge buffer overflow shall use a defined drop strategy — no stream corruption permitted.

# Software Organization

# Testing

# Hardware
