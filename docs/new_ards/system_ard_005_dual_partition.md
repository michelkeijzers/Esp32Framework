# ADR-008: Dual Partition Flash Layout from the Start

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
OTA updates are needed for maintenance without physical access. The decision was whether to include dual partition support from the beginning or add it later.

## Requirements Addressed
- SYS-REQ-040: ESPs shall use dual partition flash layout from the start

## Decision Drivers
- Dual partition required for OTA updates
- Once devices are installed in enclosures, USB access is inconvenient
- Adding dual partition later requires USB reflash of all devices
- No significant cost to include from the start
- Flash space cost is minimal on ESP32-C3 (16MB variants)

## Options Considered

### Option A: Dual Partition from the Start
Configure all devices with dual partition layout in partitions.csv.
- ✅ Pro: Ready for OTA immediately
- ✅ Pro: No USB reflash needed later
- ✅ Pro: Path prepared for staged OTA rollout
- ✅ Pro: Flash space cost is minimal (<10MB on typical devices)
- ❌ Con: Slight reduction in application partition size

### Option B: Add Dual Partition Later
Start with single partition, add dual partition when OTA is implemented.
- ✅ Pro: Maximizes application partition size initially
- ❌ Con: All deployed devices require USB reflash (inconvenient)
- ❌ Con: OTA feature blocked until all devices reflashed
- ❌ Con: Defeats the purpose of preparing for OTA early

## Decision
Adopt Option A: Dual Partition from the Start.

## Consequences
- All devices ship with dual partition layout.
- Application partition is smaller but still sufficient (~1.5MB on 16MB devices).
- OTA updates can be deployed as soon as firmware is ready.
- Rollback capability available if update fails.
- No USB reflash needed when OTA feature becomes available.
- Partitions stored in partitions.csv and automatically applied during build.
