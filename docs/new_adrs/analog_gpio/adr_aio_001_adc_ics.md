# ADR-001: Analog GPIO: ADC ICs

## Status

Accepted

## Date

2026-03-17

## Context

Multiple ways of ananlog to digital conversion is possible, and amount of pins/channels.

## Requirements Addressed

## Decision Drivers

- Cost
- Amount of analog pins
- Precision
- Ease of programming
- Precision of ADC

## Options Considered

See table:

| Feature                   | MCP3004 / MCP3008          | ADS1115                      | ESP32 GPIO ADC               |
| ------------------------- | -------------------------- | ---------------------------- | ---------------------------- |
| **Resolution**            | 10‑bit                     | 16‑bit (15‑bit ENOB)         | 12‑bit (effective 9–11‑bit)  |
| **Sample rate**           | ~200 ksps                  | 860 sps                      | ~6–18 ksps (varies by mode)  |
| **Interface**             | SPI                        | I²C                          | Internal (GPIO ADC1/ADC2)    |
| **Channels**              | 4 or 8                     | 4 (multiplexed)              | 6 (only ADC2, 6 pins)        |
| **Maximum in one system** | 6 (24/48 channels)         | 4 (16 channels)              | 6 (6 channels)               |
| **Differential inputs**   | Pseudo‑differential        | True differential            | No                           |
| **Programmable gain**     | No                         | Yes (PGA)                    | No                           |
| **Noise performance**     | Moderate                   | Very low                     | High (Wi‑Fi interference)    |
| **Voltage range**         | 0–5V (or 0–3.3V)           | ±256 mV to ±6.144V           | 0–3.3V (non‑linear)          |
| **Best for**              | Fast multi‑channel sensing | Precision, low‑level signals | Simple, non‑critical sensing |
| **Cost**                  | Around E3.5                | Around E 2                   | Free (built‑in)              |

### Option A: MCP3004/8

### Option B: ADS1115

### Option C: Direct pins

## Decision

Option C will be implemented in all cases.
Other options when needed for a project.

## Implementation Notes

## Consequences

- Maximum flexibility
