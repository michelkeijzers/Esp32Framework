# ADR-011: SK6812 RGB LEDs and Pixel Addressing Scheme

## Status
Accepted

## Date
2026-03-17

## Authors
- Project Hardware Lead

## Context
RGB LED feedback system requires choice of addressable LED strip technology and pixel numbering convention.

## Requirements Addressed
- DMX-REQ-060: System shall provide visual feedback via RGB LEDs
- DMX-REQ-070: LED behavior shall represent module state

## Decision Drivers
- Faders and encoders need independent RGB feedback
- Controller count (24 faders + 8 encoders) requires efficient hardware
- Timing consistency across multiple LED controllers
- Integration with existing WS2812/SK6812 ecosystem

## Options Considered

### Option A: SK6812 with Pixel Addressing (Selected)
Use WS2812-compatible addressable LEDs with explicit pixel numbering.
- ✅ Pro: One wire per channel (GPIO pin) for serial control
- ✅ Pro: Flexible pixel arrangement for distributed feedback
- ✅ Pro: Wide availability and ecosystem support
- ✅ Pro: Can address multiple LED arrays from single pin
- ✅ Pro: 24-bit color depth (8-bit R, G, B)
- ❌ Con: Timing-sensitive protocol (requires careful GPIO handling)
- ❌ Con: Single LED failure can affect downstream pixels

### Option B: Individual RGB Pins per LED
Direct PWM control of LED R, G, B channels.
- ✅ Pro: Simple control logic
- ✅ Pro: Not timing-sensitive
- ❌ Con: 72 GPIO pins required (3 channels × 24 LEDs) — impossible on ESP32-C3
- ❌ Con: Not feasible for I/O requirements

### Option C: TLC5940 Driver Chips
16-channel LED driver with serial control.
- ✅ Pro: Fewer GPIO pins required
- ✅ Pro: Built-in current limiting
- ❌ Con: Additional hardware complexity
- ❌ Con: Overkill for 24+8 LED count
- ❌ Con: Higher cost

## Decision
Adopt Option A: SK6812 addressable LEDs with explicit pixel addressing.

## Pixel Addressing Scheme
- Fader 0-23: Pixels 0-23 (one LED per fader)
- Encoder 0-7: Pixels 24-31 (one LED per encoder)
- Total: 32 pixels per port (can support up to 3 independent ports)

## Consequences
- Minimal hardware complexity (one GPIO pin per DMX port)
- Flexible LED feedback positioning
- Can display up to 16 million colors per pixel
- Timing requirements managed by ESP-IDF driver abstraction
- Each port supports independent LED chain (cards, pads, buttons)
- Maximum distance between pixels ~5 meters (standard limitation)
