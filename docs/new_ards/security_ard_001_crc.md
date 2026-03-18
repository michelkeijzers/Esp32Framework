# ADR-006: Multi-Level CRC Strategy for Data Integrity

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
ESP-NOW transmission can silently corrupt data. The system needs to detect and handle corrupted messages and OTA transfers. The decision was what CRC strategy to use.

## Requirements Addressed
- SEC-REQ-020, SEC-REQ-021, SEC-REQ-022: CRC protection at different levels

## Decision Drivers
- ESP-NOW hardware does not guarantee application-level payload integrity
- Silent data corruption is worse than dropped messages
- OTA transfers must be reliable with large binary sizes
- Different levels of protection needed for different message types

## Options Considered

### Option A: Multi-Level CRC Strategy (Selected)
- CRC16 on every ESP-NOW message
- CRC16 per OTA chunk (~200 bytes)
- CRC32 on full OTA binary

- ✅ Pro: Per-message detection catches transmission errors immediately
- ✅ Pro: Per-chunk CRC enables selective retransmit without full OTA restart
- ✅ Pro: Full binary CRC catches incomplete or misordered transfers
- ✅ Pro: Uses ESP-IDF built-in functions (no external library)
- ✅ Pro: Pyramidal protection matches message hierarchy
- ❌ Con: Minor overhead for CRC calculation

### Option B: No CRC Protection
Rely on ESP-NOW hardware layer.
- ✅ Pro: Minimal overhead
- ❌ Con: No application-level error detection
- ❌ Con: Silent data corruption possible
- ❌ Con: Unacceptable for OTA and critical messages

### Option C: Single CRC32 on All Messages
Use CRC32 for all messages.
- ✅ Pro: Uniform protection
- ❌ Con: More overhead per message
- ❌ Con: Cannot selectively retry OTA chunks

## Decision
Adopt Option A: Multi-Level CRC Strategy.

## Implementation Details
- Per-message: CRC16 calculated over full message including payload
- Per-chunk: CRC16 per ~200 byte OTA chunk
- Full binary: CRC32 over entire OTA binary
- Corrupted messages: Discard silently
- OTA chunk mismatch: Send NACK, requesting resend
- OTA binary mismatch: Abort OTA, trigger rollback

## Consequences
- Every message payload is protected by CRC16.
- OTA is robust to individual chunk corruption.
- Full OTA integrity is verified before commit.
- Minimal performance impact (~1% overhead).
