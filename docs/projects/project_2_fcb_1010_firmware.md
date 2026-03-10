# PROJECT 2 - FCB1010 FIRMWARE

**Purpose:** MIDI foot controller — generates MIDI and OSC from foot switches and expression pedals, merges with external MIDI device, sends to Gig Performer PC.

**ESPs:**

| ESP | Role           | Peripherals                                    | Antenna |
| --- | -------------- | ---------------------------------------------- | ------- |
| #1  | ROLE_MASTER    | None                                           | FPC     |
| #2  | ROLE_WEBSERVER | Wi-Fi, React UI, input-to-MIDI mapping, OTA    | FPC     |
| #3  | Input slave    | 2x 74HC165 (12 switches), 2x A1324 via ADS1115 | PCB     |
| #4  | Display slave  | 2x MAX7219 — custom display + 18 LEDs          | PCB     |
| #5  | MIDI slave     | MIDI IN + OUT + MERGE                          | PCB     |
| #6  | OSC slave      | OSC over Wi-Fi UDP to Gig Performer            | FPC     |

**Display slave detail:**

| Output                                       | Count       | IC                          |
| -------------------------------------------- | ----------- | --------------------------- |
| First digit segments (simplified, shows 0–1) | ~3 segments | MAX7219                     |
| Middle digit segments                        | 8 segments  | MAX7219                     |
| Last digit segments                          | 8 segments  | MAX7219                     |
| Indicator LEDs                               | 12          | MAX7219                     |
| Configuration LEDs                           | 6           | MAX7219                     |
| **Total outputs**                            | **~37**     | **2x MAX7219 (40 outputs)** |

MAX7219 RSET resistor: 3.3kΩ for 25mA per output (maximum brightness, safe practical limit).

**Input slave detail:**

| Input                           | Count | IC                         |
| ------------------------------- | ----- | -------------------------- |
| Foot switches                   | 12    | 2x 74HC165 via SPI         |
| Expression pedals (Hall sensor) | 2     | 2x A1324 → ADS1115 via I2C |

**MIDI flow:**

```
External MIDI device  →  MIDI IN (6N138)  ──┐
                                             ├──→  merge buffer  →  MIDI OUT
Webserver (generated) →  ESP-NOW → master  ──┘                  →  OSC slave → Gig Performer
```

**Power budget:**

| Component                                           | Current    |
| --------------------------------------------------- | ---------- |
| Master ESP32-C3 (ESP-NOW)                           | ~80mA      |
| Webserver ESP32-C3 (Wi-Fi)                          | ~120mA     |
| Input slave ESP32-C3 (ESP-NOW)                      | ~80mA      |
| Display slave ESP32-C3 (ESP-NOW)                    | ~80mA      |
| MIDI slave ESP32-C3 (ESP-NOW)                       | ~80mA      |
| OSC slave ESP32-C3 (Wi-Fi)                          | ~130mA     |
| 2x MAX7219 at 25mA/output (37 outputs, multiplexed) | ~115mA     |
| 2x 74HC165                                          | ~5mA       |
| 2x A1324 Hall sensors                               | ~18mA      |
| ADS1115                                             | ~2mA       |
| **Total**                                           | **~710mA** |

Recommended PSU: 5V 2A — 1290mA headroom.

**Slave code contributed:**

- `slaves/midi/` — MIDI IN/OUT/MERGE
- `slaves/display/max7219/` — custom segment and LED control, RSET 3.3kΩ
- `slaves/input/hc165/` — shift register button input
- `slaves/input/a1324/` — Hall effect pedal sensor
- `slaves/osc/` — OSC over UDP

**DD-008: MAX7219 for FCB1010 display**

- Decision: 2x MAX7219 chained via SPI for custom segment display and LEDs
- Reason: FCB1010 has custom 2.5 digit display with non-standard first digit, 12 indicator LEDs, and 6 configuration LEDs — 37 outputs total. MAX7219 provides 128 outputs across 2 ICs with built-in current limiting and multiplexing. Much cleaner to solder than 5x 74HC595.
- Alternative considered: 5x 74HC595 + ULN2803 — rejected, excessive soldering complexity on perf board
