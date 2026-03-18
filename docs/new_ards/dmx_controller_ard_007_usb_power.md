# ADR-015: USB-C Power Over 5V Regulated Supply

## Status
Accepted

## Date
2026-03-17

## Authors
- Project Hardware Lead

## Context
DMX controller requires stable power delivery for microcontroller, sensors, LEDs, and display. The decision was the primary power input and internal regulation strategy.

## Requirements Addressed
- DMX-REQ-000: System shall operate reliably across voltage range
- Non-functional requirement: Long-term battery operation (potential future)

## Decision Drivers
- Professional stage equipment uses USB-C universal standard
- Typical stage venues have USB power infrastructure
- 5V logic simplifies peripheral selection
- Regulated supply improves reliability and RF noise
- Cost-conscious component selection
- Lower voltage = safer for performers

## Options Considered

### Option A: USB-C with 5V Regulated Supply (Selected)
Use USB-C input with onboard 5V regulation.
- ✅ Pro: Universal connector (standard in pro audio)
- ✅ Pro: 5A USB power supplies readily available
- ✅ Pro: AP2127K-3.3V regulator stable and cheap
- ✅ Pro: Clean 3.3V for logic and sensors
- ✅ Pro: 5V rail for LED power (SK6812 prefer 5V)
- ✅ Pro: Built-in USB host capability (future expansion)
- ✅ Pro: Safe voltage for stage environment
- ❌ Con: Requires external power supply (not battery-operated)
- ❌ Con: USB cable required at all times

### Option B: 12V External Adapter with Regulation
Use standard 12V barrel jack connector.
- ✅ Pro: Higher voltage = smaller gauge wire
- ✅ Pro: Common in legacy audio equipment
- ❌ Con: Non-standard connector (needs universal adapter)
- ❌ Con: More heat dissipation (worse efficiency)
- ❌ Con: Higher component cost
- ❌ Con: Professional audio moving to USB

### Option C: LiPo Battery with USB Charging
Internal battery for portable operation.
- ✅ Pro: No power cable required
- ✅ Pro: Portable and cordless
- ❌ Con: Battery management complexity
- ❌ Con: Higher cost (~20 USD per 3000mAh cell)
- ❌ Con: WiFi reduces battery life to ~2 hours
- ❌ Con: Requires charging infrastructure
- ❌ Con: Not suitable for continuous stage use

### Option D: Dual Input (USB + Battery)
Hybrid approach with USB primary and battery fallback.
- ✅ Pro: Flexibility (wired or wireless)
- ✅ Pro: Graceful degradation
- ❌ Con: Significant complexity increase
- ❌ Con: Additional cost (~30 USD for charging circuit)
- ❌ Con: Not needed for Phase 1

## Decision
Adopt Option A: USB-C with 5V regulated supply.

## Power Distribution Design
- USB-C Input: 5V @ 2-3A typical
- Onboard Regulator: AP2127K-3.3V (LDO)
- Main Rail (3.3V):
  - ESP32-C3 microcontroller
  - MCP3008 ADC (analog reference)
  - ADS1115 ADC (Hall sensor)
  - SSD1306 OLED display
- Secondary Rail (5V):
  - SK6812 RGB LEDs (prefer 5V but 3.3V acceptable with resistor)
  - External sensor power (BME280, light sensor, etc.)
  - USB host port (if implemented)

## Power Budget Estimation
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
- Minimal power loss (high efficiency regulator)
- Safety isolation from performers

## Future Enhancement
Option C (LiP Battery) can be reconsidered in Phase 2 if portable remote operation becomes requirement. Would add secondary decision for battery management IC (BQ24078 or similar).
