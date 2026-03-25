# ADR-013: SSD1306 OLED Display for Status and Control

## Status
Accepted

## Date
2026-03-17

## Authors
- Project Hardware Lead

## Context
DMX controller requires a status display for device information, current DMX values, and menu interface. The decision was on display technology and driver IC.

## Requirements Addressed
- DMX-REQ-080: System shall display current DMX values
- DMX-REQ-090: System shall provide user-friendly menu interface

## Decision Drivers
- Compact form factor required (handheld footpaddle controller)
- Low power consumption (battery operation consideration)
- I2C bus available for communication
- Cost-sensitive design
- Real-time refresh capability needed

## Options Considered

### Option A: SSD1306 I2C OLED 128x64 (Selected)
Monochrome OLED display with I2C interface.
- ✅ Pro: Small form factor (1.3" display ~25×25mm)
- ✅ Pro: Sharp, high contrast image quality
- ✅ Pro: Low power consumption (~5mA at full brightness)
- ✅ Pro: I2C protocol (shared bus with ADS1115, BME280, etc.)
- ✅ Pro: Cheap (~3 USD per unit)
- ✅ Pro: Wide software ecosystem
- ✅ Pro: No backlight required (self-emissive)
- ❌ Con: Limited color depth (monochrome only)
- ❌ Con: Small resolution (128×64 or 128×32 pixels)
- ❌ Con: Lifetime concerns (OLED burn-in at 20,000+ hours)

### Option B: ILI9341 Color TFT Display (SPI)
Color LCD display with SPI interface.
- ✅ Pro: Full color (16-bit RGB)
- ✅ Pro: Larger display options available
- ✅ Pro: No burn-in issues
- ✅ Pro: Higher pixel density
- ❌ Con: Higher power consumption (~50 mA typical)
- ❌ Con: Requires backlight (battery drain)
- ❌ Con: Larger PCB footprint
- ❌ Con: SPI bus contention with MCP3008 ADC
- ❌ Con: Significant cost increase (~8-15 USD)

### Option C: ST7789 1.3" Color OLED Mini Display (SPI)
Compact color display with SPI interface.
- ✅ Pro: Small form factor
- ✅ Pro: Full color and no burn-in
- ❌ Con: Power consumption between OLED and TFT
- ❌ Con: SPI bus contention
- ❌ Con: Cost increase (~10 USD)
- ❌ Con: Less proven in hobby ecosystem

## Decision
Adopt Option A: SSD1306 I2C OLED 128×64 (1.3" diagonal).

## Display Layout
- Line 0: Device name and connection status
- Lines 1-2: DMX input channels active/disabled
- Lines 3-4: Current DMX values (first 4 channels)
- Line 5: Menu navigation indicators
- Line 6: Real-time clock or network status
- Line 7: Battery level or error messages

## Consequences
- Minimal SPI bus complexity (only ADS1115 and I2C devices)
- Low power consumption aligns with battery operation goals
- Monochrome display limits visual feedback but acceptable for text UI
- OLED burn-in mitigated by software (rotating menu, dim timeout)
- I2C address typically 0x3C or 0x3D (configurable via hardware jumper)
- Display refresh limited to ~60 Hz (sufficient for menus and status)
