# ADR-004: Master as Blind Message Router with Configurable Routing Table

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
The Master node needs to forward messages between nodes and the webserver. The decision was whether the master should understand message semantics or act as a blind router.

## Requirements Addressed
- MASTER-REQ-001: Master shall maintain routing table mapping destination MAC to node roles
- MASTER-REQ-003: Master shall route messages based on destination MAC address

## Decision Drivers
- Master must remain fully common across all projects
- No project-specific knowledge should be embedded in master
- Routing configuration must be updateable without reflashing master
- Support for monitoring copies of time-critical messages

## Options Considered

### Option A: Blind Router with Configurable MAC-Based Routing Table
Master routes messages based only on destination MAC address, with routing rules stored in NVS.
- ✅ Pro: Fully project-independent, truly common code
- ✅ Pro: Routing table can be updated via webserver without reflash
- ✅ Pro: Simple, fast routing logic
- ✅ Pro: Easy to debug and understand
- ❌ Con: Routing logic must be configured per project setup

### Option B: Semantic Router with Message Understanding
Master understands message types and routes based on content.
- ✅ Pro: More intelligent routing possible
- ❌ Con: Requires project-specific knowledge in master code
- ❌ Con: Complex and error-prone
- ❌ Con: Would fragment master code across projects

### Option C: Full SDN-Style Control
Master receives routing tables from a central controller.
- ✅ Pro: Extremely flexible
- ❌ Con: Major complexity added
- ❌ Con: Overkill for current and foreseeable needs

## Decision
Adopt Option A: Blind Router with Configurable MAC-Based Routing Table.

## Consequences
- Master code is simple and project-independent.
- Routing table is configured via webserver and stored in NVS.
- Master receives MAC address and routing configuration from webserver at boot.
- Adding new nodes requires updating the routing table on webserver.
- Direct routing enables ~6ms total latency for MIDI messages.
