# ADR-014: WiFi for Wireless Control and Network Integration

## Status
Proposed (Conditional Based on Range Requirements)

## Date
2026-03-17

## Authors
- Project Hardware Lead

## Context
DMX controller may require wireless communication for remote control, telemetry, and network integration. The decision was the wireless protocol and implementation approach.

## Requirements Addressed
- DMX-REQ-100: System shall support optional wireless communication
- DMX-REQ-110: System shall integrate with stage monitoring network

## Decision Drivers
- ESP32-C3 has integrated WiFi (802.11b/g/n)
- Professional audio environments often have enterprise WiFi
- Remote control enables convenient operation from lighting board
- Network integration enables monitoring and configuration from PC
- BLE has limited range (~10 meters typical) unsuitable for large venues
- Performance requirements (real-time DMX) require low latency

## Options Considered

### Option A: WiFi (2.4 GHz 802.11b/g/n) (Selected as Primary)
Use internal WiFi radio for network connectivity.
- ✅ Pro: Built-in on ESP32-C3 (no additional hardware)
- ✅ Pro: Range: 50-100+ meters (stage to FOH console)
- ✅ Pro: Low latency: 1-50 ms (acceptable for real-time control)
- ✅ Pro: Personal Area Network (no infrastructure required)
- ✅ Pro: Professional audio venues have WiFi infrastructure
- ✅ Pro: Can support remote management and monitoring
- ✅ Pro: Higher bandwidth for telemetry and logging
- ✅ Pro: Coexists with BLE if needed (dual-mode)
- ❌ Con: Higher power consumption (~80-200 mA transmitting)
- ❌ Con: Potential RF interference in dense RF environments
- ❌ Con: Security considerations (WPA3 required)

### Option B: Bluetooth Low Energy (BLE)
Use internal BLE radio for short-range communication.
- ✅ Pro: Much lower power consumption (~10-30 mA)
- ✅ Pro: Simple pairing model
- ❌ Con: Limited range (~10 meters line-of-sight)
- ❌ Con: Not suitable for large venue operation
- ❌ Con: Incompatible with existing WiFi infrastructure
- ❌ Con: Single connection limitation

### Option C: Wired (USB or Ethernet) Only
No wireless support; wired communication only.
- ✅ Pro: Lowest power consumption (no RF)
- ✅ Pro: Most reliable (no RF interference)
- ✅ Pro: No security vulnerabilities
- ❌ Con: Limited mobility (cable constraints)
- ❌ Con: Not suitable for professional stage use
- ❌ Con: Impractical for distributed controllers

### Option D: Hybrid WiFi + BLE
Support both WiFi and BLE simultaneously.
- ✅ Pro: Best of both worlds (range AND efficiency)
- ✅ Pro: Can switch between modes
- ✅ Pro: WiFi for venue integration, BLE for local mobile
- ❌ Con: Increased code complexity
- ❌ Con: Not required for current scope

## Decision
Adopt Option A: WiFi for primary wireless communication.

## Implementation Notes
- Enterprise WiFi network recommended (WPA3, 5GHz preferred for interference avoidance)
- Local Area Network (LAN) mode if WiFi unavailable: direct AP creation
- Network protocol: OSC or WebSocket over TCP/IP for real-time control
- Telemetry logged to network-accessible server (optional)
- Fallback to wired USB if wireless fails

## Consequences
- Professional-grade wireless operation suitable for large venues
- Network integration enables remote monitoring and control
- WiFi power consumption requires USB or mains power (not battery-only)
- Security hardening required (HTTPS, authentication, encryption)
- RF testing recommended in venue environment before deployment
- Potential for interference in dense RF environments (mitigation: channel scanning)

## Future Enhancement
Option D (Hybrid WiFi + BLE) can be added in Phase 2 if battery-operated remote handheld is required (separate decision point).
