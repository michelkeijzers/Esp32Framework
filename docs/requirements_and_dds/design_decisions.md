# Design Decisions

**DD-001: Master is a blind router**

- Decision: Master reads only destination MAC, never payload content
- Reason: Keeps master fully generic — never needs to be reflashed between projects. Project logic belongs in webserver slave only.
- Alternative considered: Master interprets message type to make routing decisions — rejected, would require project specific code in master

**DD-002: MIDI notes bypass webserver — direct routing to OSC slave**

- Decision: MIDI note messages routed master → OSC slave directly, with parallel monitoring copy to webserver
- Reason: Via webserver adds ~11-20ms latency including FreeRTOS scheduling jitter — unacceptable for live music. Direct routing achieves ~6ms total.
- Alternative considered: All messages via webserver — rejected, latency too high for performance use

```
Via webserver:  MIDI → master → webserver → master → OSC → UDP  ~11-20ms
Direct:         MIDI → master → OSC → UDP                        ~6ms
```

---

**DD-003: Webserver slave generates MIDI messages**

- Decision: Webserver slave owns all input-to-MIDI mapping logic and generates MIDI messages from input events
- Reason: Mapping is project configuration — belongs in the brain of the system. Configurable via React UI without reflashing. Input slave stays generic.
- Alternative considered: Input slave generates MIDI directly — rejected, would require project specific code in slave and lose configurability

---

**DD-004: Slave code is fully generic — NVS data varies per project**

- Decision: All slave code identical across projects, only NVS contents differ
- Reason: Build once, reuse forever. Adding a slave to a new project is configuration, not development.
- Alternative considered: Per-project slave variants — rejected, would fragment codebase and lose reusability

---

**DD-005: Antenna selection per role**

- Decision: U.FL + FPC antenna for master, remote, webserver, OSC slave. PCB built-in antenna for all other slaves.
- Reason: Master, remote, webserver, and OSC slave require reliable Wi-Fi or long range ESP-NOW. Slaves are close to master, inside plastic enclosures — PCB antenna sufficient. FPC adds ~0.50 euro per ESP, cost justified only where needed.
- OTA impact: Slaves with PCB antenna inside metal enclosures cannot reliably use temporary Wi-Fi OTA — OTA proxy via ESP-NOW is the long term solution for these cases.
- Alternative considered: FPC on all ESPs — rejected, unnecessary cost for slaves that are close range and plastic enclosed. Reconsidered if metal enclosures are used.

---

**DD-006: Single VS Code project, role per config.h**

- Decision: One codebase, one project, THIS_DEVICE_ROLE in config.h selects role at compile time
- Reason: All roles share common components. Easy to maintain. CMake only compiles what is needed.
- Alternative considered: Separate project per role — valid for larger teams, premature for current scale. Can migrate later when roles diverge significantly.

---

**DD-007: Build and validate one slave at a time**

- Decision: Build master first, then add one slave at a time in order of increasing complexity
- Reason: Each step introduces exactly one new unknown. Never debug two unknowns simultaneously.
- Order: Master → input slave → webserver → display slave → DMX slave

---

**DD-008: MAX7219 for FCB1010 display**

- Decision: 2x MAX7219 chained via SPI for custom segment display and LEDs
- Reason: FCB1010 has custom 2.5 digit display with non-standard first digit, 12 indicator LEDs, and 6 configuration LEDs — 37 outputs total. MAX7219 provides 128 outputs across 2 ICs with built-in current limiting and multiplexing. Much cleaner to solder than 5x 74HC595.
- Alternative considered: 5x 74HC595 + ULN2803 — rejected, excessive soldering complexity on perf board

---

**DD-009: 74HC165 for FCB1010 button input**

- Decision: 2x 74HC165 shift registers chained via SPI for 12 switches
- Reason: 12 buttons exceed direct GPIO availability. 74HC165 uses same SPI bus as MAX7219, no additional wiring complexity.
- Alternative considered: MCP23017 via I2C — valid, but SPI already in use for display, 74HC165 simpler for pure input

---

**DD-010: A1324 Hall effect sensor for foot pedals**

- Decision: A1324 linear Hall effect sensor with ADS1115 ADC for continuous pedal position
- Reason: Magnetic sensing is wear-free — no mechanical contact, suitable for foot pedal with high cycle count. A1324 outputs analog voltage proportional to magnetic field, ADS1115 provides 16-bit resolution.
- Alternative considered: Potentiometer — rejected, mechanical wear over time

---

**DD-011: MIDI merge buffer in MIDI slave**

- Decision: MIDI slave implements a merge buffer combining external MIDI IN (UART RX) with internally generated messages (ESP-NOW from master)
- Reason: FCB1010 must pass through external MIDI device while also generating its own MIDI — single MIDI OUT must carry both streams without corruption.
- Queue size: 32 messages, configurable via `MIDI_MERGE_QUEUE_SIZE`

---

**DD-012: Slave code library grows per project**

- Decision: Each project contributes reusable slave components to the shared library
- Reason: After two projects the library covers most common stage peripherals. Future projects are assembly of existing components, not new development.
- Project 1 adds: dmx, tm1637, gpio input
- Project 2 adds: midi, max7219, hc165, a1324, osc

---

**DD-013: Prefer additional ESP slave over UART expander IC**

- Decision: When a slave requires more than one UART, add a second ESP slave rather than using a UART expander IC such as SC16IS752
- Reason: Additional ESP slave costs the same (~2 euro), provides a full independent CPU, keeps each slave simple, fits the design philosophy of one role per ESP
- Alternative considered: SC16IS752 UART expander via I2C — rejected, same cost, added complexity, no architectural benefit

---

**DD-014: OTA strategy — three approaches**

- Decision: Three OTA approaches supported, used based on situation
- Approach 1 — Webserver slave via Wi-Fi: standard ESP-IDF OTA, already in design, works today
- Approach 2 — Slaves via temporary Wi-Fi: slave temporarily enables Wi-Fi STA, connects to router, downloads firmware, returns to ESP-NOW only mode. Works for plastic enclosure slaves close to router.
- Approach 3 — OTA proxy via ESP-NOW: webserver downloads firmware via Wi-Fi, pushes to slave via ESP-NOW chunks (~2500 chunks at 200 bytes each). No Wi-Fi needed on slave. Works regardless of enclosure or antenna. Deferred — significant development effort.
- Reason: Slaves are inside enclosures, USB access is inconvenient. Wireless OTA needed for maintenance without physical access.
- Alternative considered: USB only — rejected, impractical once installed in enclosures

---

**DD-015: Dual partition flash on all ESPs from the start**

- Decision: All ESPs configured with dual partition flash layout in partitions.csv from the beginning
- Reason: Adding OTA support later without dual partition would require USB reflash anyway. Cost is only flash space — no hardware change needed.
- Alternative considered: Add dual partition later — rejected, defeats the purpose of OTA

---

**DD-016: FreeRTOS tick rate 1000Hz**

- Decision: CONFIG_FREERTOS_HZ=1000 in sdkconfig.defaults
- Reason: Task wake-up resolution of 1ms needed for reliable sub-10ms message handling. Without 1ms tick, a received ESP-NOW packet may wait up to 10ms before the handling task wakes up — adding unacceptable jitter to MIDI latency.
- Overhead: ~0.1-0.2% CPU — negligible on ESP32-C3 at 160MHz
- Alternative considered: Default 100Hz (10ms tick) — rejected, insufficient scheduling resolution for latency requirements

---

**DD-017: CRC strategy — two levels**

- Decision: CRC16 on every ESP-NOW message, CRC16 per OTA chunk, CRC32 on full OTA binary
- Reason: ESP-NOW transmission can corrupt data — silent corruption is worse than a dropped message. Two-level CRC in OTA catches both per-chunk transmission errors and incomplete or misordered transfers.
- Implementation: ESP-IDF built-in `esp_crc16_le()` and `esp_crc32_le()` — no external library needed
- Per message: CRC16 over full message including payload — mismatch → discard silently
- Per OTA chunk: CRC16 — mismatch → NACK → resend
- Full OTA binary: CRC32 — mismatch → abort OTA → rollback
- Alternative considered: No CRC, rely on ESP-NOW hardware — rejected, hardware layer does not guarantee payload integrity at application level
