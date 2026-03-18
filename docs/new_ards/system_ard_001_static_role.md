# ADR-001: Static Role Definition at Compile Time

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
The system must support different roles (Master, Remote, Webserver, Node) for different ESP32 devices. The design decision was whether roles should be determined at compile time or runtime.

## Requirements Addressed
- SYS-REQ-002: Role determination strategy

## Decision Drivers
- Simplicity of implementation
- Compile-time knowledge needed for configuration
- Reduced attack surface and misconfiguration risk
- No need for dynamic role switching during normal operation

## Options Considered

### Option A: Compile-Time Role Definition
Each ESP is compiled with a specific role, no runtime switching possible.
- ✅ Pro: Simple implementation, no runtime overhead
- ✅ Pro: Reduced risk of misconfiguration
- ✅ Pro: Smaller code footprint
- ❌ Con: Requires recompilation and reflash to change role

### Option B: Runtime Role Selection
Role is selected at boot time and can be changed during operation.
- ✅ Pro: Can change role without recompilation
- ❌ Con: Adds complexity and potential for misconfiguration
- ❌ Con: Runtime overhead for role checking
- ❌ Con: Increased code complexity

## Decision
Adopt Option A: Compile-Time Role Definition.

## Consequences
- Each ESP must be compiled with its specific role via preprocessor defines.
- Changing role requires recompilation and reflash.
- Eliminates runtime role ambiguity.
- Code is optimized for the single role being compiled.
