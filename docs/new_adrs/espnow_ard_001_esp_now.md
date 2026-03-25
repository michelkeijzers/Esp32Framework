# ADR-003: ESP-NOW for Inter-ESP Communication

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
Multiple ESP devices need to communicate with each other. The decision was which communication protocol to use.

## Requirements Addressed
- ESPNOW-REQ-001: ESP-NOW shall be used for all inter-ESP communication

## Decision Drivers
- Low-latency requirements for real-time audio (MIDI)
- Low power consumption requirements
- No infrastructure (no Wi-Fi AP or Bluetooth pairing needed)
- Direct point-to-point communication
- Connectionless protocol suitable for broadcast scenarios

## Options Considered

### Option A: ESP-NOW
Uses ESP-NOW 802.11 wireless protocol for peer-to-peer communication.
- ✅ Pro: Sub-millisecond latency
- ✅ Pro: Low power consumption
- ✅ Pro: No infrastructure needed
- ✅ Pro: Connectionless, reliable delivery to known peers
- ❌ Con: 250 byte payload limit
- ❌ Con: No built-in reliability guarantees

### Option B: Wi-Fi
Uses standard Wi-Fi with TCP/UDP sockets for inter-ESP communication.
- ✅ Pro: Unlimited message size
- ✅ Pro: Mature stack
- ❌ Con: Higher latency (10-50ms typical)
- ❌ Con: Infrastructure required (AP)
- ❌ Con: Higher power consumption
- ❌ Con: Not suitable for real-time audio applications

### Option C: Bluetooth
Uses Bluetooth for inter-ESP communication.
- ❌ Con: Similar or worse latency than Wi-Fi
- ❌ Con: Pairing overhead
- ❌ Con: Higher complexity
- ❌ Con: Higher power consumption

## Decision
Adopt Option A: ESP-NOW for all inter-ESP communication.

## Consequences
- Maximum message payload is 250 bytes.
- Must include message headers for sequence numbers, version, and CRC.
- Messages must include addressing to reach specific peers.
- Broadcast capability available for monitoring copies.
- Packet loss is possible and must be handled at application level.
