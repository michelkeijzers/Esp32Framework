# DMX Controller Hardware Architecture Record Index

## Overview

This directory contains Architecture Decision Records (ARDs) documenting major hardware design decisions for the Esp32Framework DMX controller project.

## Hardware Component ARDs

### Core Sensor & Input Devices

- **[ADR-010: A1324 Hall Effect Sensor](dmx_controller_ard_002.md)** — Foot pedal position measurement
  - Selected for wear-free operation and 16-bit resolution
  - Enabled by ADS1115 16-bit I2C ADC
  - Expected lifespan: 100,000+ cycles

- **[ADR-012: MCP3008 SPI ADC](dmx_controller_ard_004.md)** — Analog input multiplexing
  - 8-channel A/D converter for fader inputs
  - Supports up to 3 chips (24 channels total)
  - Provides interface for potentiometers, Hall sensors, and sensors

### Display & User Feedback

- **[ADR-011: SK6812 RGB LEDs](dmx_controller_ard_003.md)** — Visual feedback system
  - Addressable LED strips for per-channel feedback
  - Pixel addressing scheme; 32 pixels per port
  - Supports 24-bit color depth; 16 million colors

- **[ADR-013: SSD1306 OLED Display](dmx_controller_ard_005.md)** — Status and control interface
  - 128×64 monochrome OLED via I2C
  - Real-time DMX value display and menu interface
  - Low power consumption (~5 mA at full brightness)

### Wireless & Connectivity

- **[ADR-014: WiFi (802.11b/g/n)](dmx_controller_ard_006.md)** — Wireless communication
  - Range: 50-100+ meters (suitable for large venues)
  - Low latency: 1-50 ms
  - Built-in on ESP32-C3; integrated with LAN mode fallback

### Power Management

- **[ADR-015: USB-C 5V Regulated Supply](dmx_controller_ard_007.md)** — Power input and regulation
  - USB-C connector (professional and universal)
  - 5V primary bus with 3.3V LDO regulator
  - Estimated power budget: 200-250 mA (idle), 750-900 mA (peak)
  - Recommended PSU: 2A minimum, 3A preferred

## Hardware Summary

| Component           | Decision           | Rationale                                        |
| ------------------- | ------------------ | ------------------------------------------------ |
| **Microcontroller** | ESP32-C3           | (See ADR-001)                                    |
| **Pedal Position**  | A1324 Hall sensor  | Wear-free, 16-bit resolution, professional-grade |
| **Fader Inputs**    | MCP3008 (3×)       | Low cost, SPI interface, supports 24 channels    |
| **Visual Feedback** | SK6812 RGB LEDs    | Addressable, per-channel control, 16M colors     |
| **Display**         | SSD1306 OLED       | Monochrome, I2C, low power, compact              |
| **Wireless**        | WiFi 2.4 GHz       | Range suitable for venues, low latency, built-in |
| **Power Input**     | USB-C 5V regulated | Universal standard, clean 3.3V rail, safe        |

## Electrical Constraints

### I2C Bus Devices

- ESP32-C3 GPIO21 (SDA), GPIO20 (SCL)
- Pullup resistors: 4.7kΩ (standard)
- Max frequency: 400 kHz (standard mode)
- **Devices on bus:**
  - ADS1115 ADC (Hall sensor): address 0x48
  - SSD1306 OLED: address 0x3C or 0x3D
  - BME280 sensor: address 0x76
  - Other future sensors

### SPI Bus Devices

- ESP32-C3 GPIO6 (MOSI), GPIO4 (MISO), GPIO7 (SCK)
- Speed: up to 10 MHz (limited by MCP3008 @ 10 MHz)
- **Devices on bus:**
  - MCP3008×3 ADC (Chip Select pins: GPIO5, GPIO8, GPIO1)
  - (Future: SD card, other SPI devices)

### UART/Serial Communication

- ESP32-C3 GPIO20 (RX), GPIO21 (TX) — Debug console
- **DMX Output:** (See soft-UART or DMX driver documentation)

### GPIO Pin Allocation

| GPIO       | Function    | Notes                                |
| ---------- | ----------- | ------------------------------------ |
| **GPIO0**  | Boot select | Pull-up during normal execution      |
| **GPIO1**  | MCP3008 CS  | Chip select for ADC #3               |
| **GPIO2**  | Available   | Can be used for sensors or expansion |
| **GPIO3**  | USB D-\*\*  | Reserved (USB functionality)         |
| **GPIO4**  | SPI MISO    | Shared with MCP3008                  |
| **GPIO5**  | MCP3008 CS  | Chip select for ADC #1               |
| **GPIO6**  | SPI MOSI    | Shared with MCP3008                  |
| **GPIO7**  | SPI CLK     | Shared with MCP3008                  |
| **GPIO8**  | MCP3008 CS  | Chip select for ADC #2               |
| **GPIO9**  | LED Output  | Status LED or RGB control            |
| **GPIO10** | SK6812 Data | Addressable LED chain                |
| **GPIO19** | Available   | Can be used for sensors              |
| **GPIO20** | I2C SDA     | Shared with ADS1115, OLED, etc.      |
| **GPIO21** | I2C SCL     | Shared with ADS1115, OLED, etc.      |

## Power Budget Breakdown

- **Static (idle, no WiFi):** ~50 mA
  - ESP32-C3 core: ~30 mA
  - OLED display: ~10 mA
  - Sensors: ~10 mA
- **WiFi Active:** +150-200 mA
  - WiFi radio: 150-200 mA (transmit/receive)
- **RGB LEDs:** ~20 mA per pixel at white full brightness
  - 32 pixels × 20 mA = 640 mA (peak, all on white)
  - Typical: 100-300 mA (mixed colors, duty cycle)

- **Total (WiFi + partial LEDs):** 250-500 mA typical, 750-900 mA peak

## Design Philosophy

These decisions prioritize:

1. **Professional durability** — Suitable for venue/studio use
2. **Cost-effectiveness** — Minimized BOM without sacrificing quality
3. **Modularity** — Easy to extend with additional sensors/outputs
4. **Reliability** — Well-established components with proven ecosystems
5. **Simplicity** — Minimal board complexity, leveraging built-in peripherals

## Next Steps

- PCB layout with these constraints
- Detailed schematic review against this ADR
- Prototype validation of WiFi/RF interference
- Firmware driver development for each component
