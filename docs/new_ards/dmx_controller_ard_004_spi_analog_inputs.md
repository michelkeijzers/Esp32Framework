# ADR-012: MCP3008 SPI ADC for Analog Input Channels

## Status
Accepted

## Date
2026-03-17

## Authors
- Project Hardware Lead

## Context
DMX controller has multiple analog input channels (faders, encoders, expression pedal) that require conversion to digital values. The decision was the ADC hardware strategy.

## Requirements Addressed
- DMX-REQ-020: System shall have 24 fader inputs
- DMX-REQ-030: System shall have 8 encoder inputs
- DMX-REQ-040: System shall support expression pedal control

## Decision Drivers
- ESP32-C3 has limited ADC pins (8 total, not all available for external use)
- Multiple analog sources require parallel input capability
- SPI bus available and shared with other peripherals
- Cost-conscious but reliable solution needed

## Options Considered

### Option A: MCP3008 8-Channel SPI ADC (Selected)
Use SPI-based analog-to-digital converter.
- ✅ Pro: 8 independent analog channels from single SPI device
- ✅ Pro: Low cost (~2 USD per chip)
- ✅ Pro: SPI bus shared with other devices
- ✅ Pro: Daisy-chaining supported (multiple MCP3008 on same SPI)
- ✅ Pro: 10-bit resolution sufficient for fader/pedal control
- ✅ Pro: Wide voltage range (0-5V with external reference)
- ❌ Con: Slightly slower than internal ADC (100 kHz max)
- ❌ Con: Adds SPI devices to bus (timing consideration)

### Option B: Internal ESP32-C3 ADC Only
Use onboard ADC without external chips.
- ✅ Pro: No additional hardware (cheaper BOM)
- ✅ Pro: Faster conversion (~1 MHz)
- ✅ Pro: Lower latency
- ❌ Con: Only 8 available ADC pins total
- ❌ Con: Some pins reserved for boot, strapping
- ❌ Con: Cannot support 24 independent faders
- ❌ Con: Timing conflicts with other peripherals (UART, SPI, WiFi)

### Option C: Multiple MCP3004 (4-channel) Chips
Use multiple 4-channel ADCs instead of 8-channel.
- ✅ Pro: Same cost per channel
- ✅ Pro: More granular control
- ❌ Con: Requires more SPI chip select pins (3 required)
- ❌ Con: More complex PCB wiring
- ❌ Con: Higher cost for same functionality

## Decision
Adopt Option A: MCP3008 8-Channel SPI ADC.

## Implementation Notes
- Three MCP3008 chips provide 24 analog channels (for 24 faders)
- Daisy-chain on single SPI bus minimizes pin usage
- CLK pin shared, CS (chip select) per device
- Polling frequency: 100 Hz per channel sufficient for musical control
- 10-bit resolution (0-1023) adequate for fader granularity

## Consequences
- Minimal GPIO pin usage (only SPI + 3 chip selects)
- Scalable to multiple ADC chips without hardware redesign
- Modest latency increase (10 ms per full scan) acceptable for faders
- SPI bus must be managed carefully with other devices (SD, display)
- I2C bus remains free for sensors and expansion
