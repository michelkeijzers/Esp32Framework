# ADR-009: 74HC165 Shift Registers for FCB1010 Button Input

## Status
Accepted

## Date
2026-03-17

## Authors
- Project Hardware Lead

## Context
FCB1010 footswitch has 12 buttons but ESP32-C3 has limited GPIO pins. The decision was how to interface the 12 buttons.

## Requirements Addressed
- DMX-REQ-042: System shall read footswitch input via appropriate interface

## Decision Drivers
- 12 buttons exceed direct GPIO availability on ESP32-C3
- MAX7219 display driver already uses SPI bus for TM1637
- Need for cost-effective solution
- Minimal wiring complexity desired

## Options Considered

### Option A: 74HC165 Shift Registers (Selected)
Chain 2x 74HC165 8-bit shift registers via SPI, same bus as MAX7219.
- ✅ Pro: Uses existing SPI bus (no additional wiring)
- ✅ Pro: Cost-effective (~0.50 USD per chip)
- ✅ Pro: Simple SPI protocol for reading
- ✅ Pro: Proven design, widely available
- ❌ Con: Requires bit-banging GPIO read logic
- ❌ Con: Additional duty cycle for reading buttons

### Option B: MCP23017 I/O Expander
MCP23017 16-bit I/O expander via I2C.
- ✅ Pro: Single chip for all 16 bits
- ✅ Pro: Clean I2C interface
- ❌ Con: Requires separate I2C bus setup
- ❌ Con: ~1 USD cost vs 0.50 USD for 74HC165
- ❌ Con: Register complexity

## Decision
Adopt Option A: 74HC165 Shift Registers.

## Consequences
- 2x 74HC165 chips chained on existing SPI bus
- GPIO input node firmware includes SPI shift register reading logic
- Button read latency ~100-200us (acceptable)
- Simple, cost-effective hardware solution
- Straightforward to extend to more buttons if needed (add more 74HC165s)
