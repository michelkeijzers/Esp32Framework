# ADR-001: Power

## Status

Accepted

## Date

2026-03-17

## Context

DMX controller requires stable power delivery for microcontroller, sensors, LEDs, and display. The decision was the primary power input and internal regulation strategy.

## Requirements Addressed

## Decision Drivers

- Correct power
- Enough current
- Easyiness of implementation

## Options Considered

### Option A: Barrel plug with 5V 1A adapter (Selected)

A standard 5V adapter with center positive pin, 1A. The barrel will be 5.5/2.5mm (standard).

- ✅ Pro: Universal connector
- ✅ Pro: 5A USB power adapter readily available
- ❌ Con: Delicate barrel plug
- ❌ Con: Separate adapter always needed

### Option B: 220V IEC plug with builtin adapter.

- ✅ Pro: Strong power cable/plug
- ✅ Pro: Builtin adapter
- ❌ Con: Huge plug
- ❌ Con: More space neede within enclosure
- ❌ Con: Slightly more manufacturing effort

## Decision

Adopt Option A: 5V adapter with barrel plug.

# Power Budget Estimation

- ESP32-C3 idle: ~30 mA
- ESP32-C3 WiFi active: ~150-200 mA
- RGB LEDs (full white): ~600 mA (for 32 pixels @ 20mA each)
- OLED display: ~10-20 mA
- Sensors: ~5 mA
- **Total typical: 200-250 mA (idle), 750-900 mA (peak)**
- **Recommended PSU: 2A minimum, 3A preferred**

## Consequences

- Stable, professional-grade operation
- WiFi and real-time DMX performance optimized
- No battery management complexity
- Suitable for 24/7 venue operation (always plugged in)
