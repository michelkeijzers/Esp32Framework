# ADR-DIO-001: Digital GPIO Pins Extension
## Status
Accepted, Implement when needed (per part)

## Date
2026-03-17

## Context
Typically more GPIO pins are needed than the amount of GPIO pins being available on the ESP, especially when an ESP C3 is used. 

## Requirements Addressed
TODO

## Decision Drivers
- Cost effective
- Minimal wiring complexity desired

## Options Considered

### Option A: Direct Pins

Connecting an input or output directly to a GPIO pin.
- ✅ Pro: Very cost effective
- ✅ Pro: Easy wiring
- ✅ Pro: Easy programming
- ✅ Pro: Interrupt support
- ✅ Pro: Input or output
- ❌ Con: Limited amount of free to use GPIO pins

Practical maximum: around 7-8 inputs and outputs combined.

### Option B: 74HC165/74HC595 Shift Registers
- ✅ Pro: Uses existing SPI bus, one CS
- ✅ Pro: Cost-effective, 74HC165 ICs are cheap
- ✅ Pro: Practically, 32 ICs in one chain totalling 256 inputs OR outputs
- ✅ Pro: Multiple chains can be used (using CS pins) where each can be input or output chains.
- ❌ Con: Only for INPUTS (74HC165) or OUTPUTS (74HC595)
- ❌ Con: Requires bit-banging GPIO read logic
- ❌ Con: Additional duty cycles/latency for reading
- ❌ Con: Hard to mix inputs and outputs within one chain (but not needed).

Practical maximum: max 2 chains on an ESP32 (7 free pins if UART is used, 2 for shared signals CLK, MISO/MOSI) and 2 per chain (CS and Latch). Thus the practical maximum is 2 chains: 256 inputs, 256 outputs or 128 inputs/128 outputs.

### Option C: MCP23017 I/O Expander
MCP23017 16-bit I/O expander via I2C.
- ✅ Pro: Single chip for all 16 bits
- ✅ Pro: Clean I2C interface
- ✅ Pro: Supports interrupt
- ✅ Pro: Any combination of input or output pin setup
- ✅ Pro: Only two pins
- ✅ Pro: Upto 8 ICs can be connected.
- ✅ Pro: Reduced latency
- ❌ Con: Requires separate I2C bus setup
- ❌ Con: Slightly more expensavie than 74HC166/74HC595
- ❌ Con: Register complexity

Maximum: 128 inputs/outputs in any combination.

## Decision
Option A will be implemented.
Option B and C will be implement whenever there is a need for a project for it.

## Consequences
Maximum possibilities without the need for unnecessary development time.
