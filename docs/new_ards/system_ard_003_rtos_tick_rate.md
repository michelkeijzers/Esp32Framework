# ADR-005: FreeRTOS Tick Rate 1000Hz for Real-Time Performance

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
The system needs to handle time-critical messages (MIDI note on/off) with low latency. The decision was what FreeRTOS tick rate to use.

## Requirements Addressed
- SYS-REQ-030: FreeRTOS tick rate shall be 1000Hz (1ms tick)
- SYS-REQ-031: Direct routing shall achieve ~6ms total latency

## Decision Drivers
- MIDI messages have strict latency requirements (<10ms perceived latency)
- Task wake-up jitter directly impacts message handling latency
- ESP32-C3 at 160MHz can easily handle 1000Hz tick rate
- CPU overhead of increased tick rate is negligible (~0.1-0.2%)

## Options Considered

### Option A: 1000Hz Tick Rate (1ms)
Default FreeRTOS configuration with 1ms scheduling resolution.
- ✅ Pro: Sub-millisecond wake-up jitter for time-critical tasks
- ✅ Pro: Achieves ~6ms total latency for MIDI messages
- ✅ Pro: Negligible CPU overhead on ESP32-C3 (~0.1-0.2%)
- ❌ Con: Slightly higher overhead than default

### Option B: 100Hz Tick Rate (10ms) - Default
Default ESP-IDF configuration with 10ms scheduling resolution.
- ✅ Pro: Lower overhead
- ❌ Con: 10ms scheduling jitter unacceptable for MIDI timing
- ❌ Con: Increases total latency to 11-20ms (noticeable by musicians)
- ❌ Con: Cannot reliably handle sub-10ms deadlines

### Option C: Variable Tick Rate
Increase tick rate only when needed.
- ✅ Pro: Reduces power consumption at idle
- ❌ Con: Adds complexity with minimal benefit
- ❌ Con: Master boots at high rate anyway

## Decision
Adopt Option A: 1000Hz Tick Rate (1ms).

## Consequences
- Configurable via sdkconfig.defaults: CONFIG_FREERTOS_HZ=1000
- All tasks wake within 1ms of their event
- Total MIDI latency achieved is ~6ms (acceptable for real-time performance)
- CPU overhead is negligible and acceptable for the use case
- All tasks can rely on 1ms scheduling resolution guarantees
