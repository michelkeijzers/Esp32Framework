**Purpose:** Control a DMX universe from a footswitch with display feedback and browser based configuration.

**Website Pages**

- Home page:
  - Navigation buttons to other pages:
- Control Page
  - Buttons for each preset (2-20)
  - Button Blackout
  - Button Previous Preset
  - Button Next Preset
- DMX Presets Page:
  - List with presets (index + name).
  - Button Add Preset
  - Button Delete Preset
  - Button Move Up Preset
  - Button Move Down Preset
  - Button Edit Preset
- Edit Preset Preset
  - Text Box Name (editable)
  - List/Grid with 512 pairs of index and DMX value
  - Clicking a value shows Edit Value Page
- Edit Value Page
  - Button 10 digits
  - Button Cancel
  - Button Enter
- Configuration Page
  - Button Load
  - Button Save
  - Configuration items
- Status Page
  - List of ESP devices with Role, Sequence Number, Status
- Initialization
  - List of ESP devices with Role, Sequence Number, MAC Address
  - Text Box MAC Address, editable
  - Button Send
- Security
  - Text Box New Security Key (16 byte hex string), editable
  - Button Send New Key
- Logging Page
  - Textbox (noneditable) with logging text
  - Scrollbar
- Firmware Page
  - List of ESP devices with Role, Sequence Number, Firmware Version
  - Button Firmware Update (of selected ESP)
  - Line for OTA status
- Manual Page
  - HTML

  - Update Firmware button for each device, with status (e.g. "up to date", "update available", "updating...", "update failed")

- Home page, with navigation buttons mostly to pages.

- DMX Presets page, with buttons to add/delete/moving presets up/down, and a list that shows the presets names.

- DMX Preset Page: When clicking on a preset (or with edit page), navigation shows the name and 512 values of the selected preset.

- DMX Value Edit Page: The selected value (out of 512) can be changed by big digit buttons for easy usage on mobile phone.

- Firmware page, with a list of (editable) MAC addresses, and a Update Firmware button PER ESP device and status.

- Status page, with all ESP32s in the system, including their status.

- Logging page, with logging (ppossibly table formatted with timestamp, source DSP and text)

- Manual (Help) Page

- Configuration page: configuration for various ESPs, with separate LOAD and SAVE button.

- Control page, with current preset, and buttons to select preset (2-20?), and Blackout button.

**ESPs:**

| ESP | Role           | Peripherals                          | Antenna |
| --- | -------------- | ------------------------------------ | ------- |
| #1  | ROLE_MASTER    | None                                 | FPC     |
| #2  | ROLE_WEBSERVER | Wi-Fi, Htmx UI, OTA                  | FPC     |
| #3  | Input slave    | Single footswitch — direct GPIO      | PCB     |
| #4  | Display slave  | TM1637 seven segment, max brightness | PCB     |
| #5  | DMX slave      | MAX3485, XLR, named universes in NVS | PCB     |

**Power budget:**

| Component                        | Current    |
| -------------------------------- | ---------- |
| Master ESP32-C3 (ESP-NOW)        | ~80mA      |
| Webserver ESP32-C3 (Wi-Fi)       | ~120mA     |
| Input slave ESP32-C3 (ESP-NOW)   | ~80mA      |
| Display slave ESP32-C3 (ESP-NOW) | ~80mA      |
| DMX slave ESP32-C3 (ESP-NOW)     | ~80mA      |
| TM1637 display (max brightness)  | ~40mA      |
| MAX3485 DMX                      | ~10mA      |
| Footswitch pull-up               | ~1mA       |
| **Total**                        | **~491mA** |

| Messages           | From              | To             | Message parameters |
| ------------------ | ----------------- | -------------- | ------------------ |
| Load Configuration | Webserver         | All slaves     | -                  |
| Button Pressed     | General I/O Slave | Webserver      | Short/Long Press   |
| Select Preset      | Webserver         | DMX slave      | Preset number      |
| Heartbeat          | All slaves        | Master         | Time stamp         |
| OTA Update         | Webserver         | Specific slave | TODO               |

- Every messages has a response message for success or failure, with error details if applicable.

Note that all message contain:

- Version number
- MAC Address

NVS Storage:

| ESP         | NVS Namespace     | NVS Key                         | Type    | Stored Data                                                   |
| ----------- | ----------------- | ------------------------------- | ------- | ------------------------------------------------------------- |
| Master      | Mac Addresses     | mac_address\_\<x\>              | string  | MAC address of slave \<x\>                                    |
| Web Server  | DMX Preset        | index                           | int16_t | Currently selected DMX preset number                          |
| DMX Slave   | DMX Presets       | preset\_\<x\>\_name             | string  | Name of preset \<x\>                                          |
| DMX Slave   | DMX Presets       | preset\_\<x\>\_universe         | int8_t  | Universe Number (\*2)                                         |
| DMX Slave   | DMX Presets       | preset\_\<x\>\_data             | blob    | DMX values for preset \<x\>                                   |
| DMX Slave   | DMX Configuration | preset\_\<x\>\_active           | int8_t  | Inactive (0), Active (1)                                      |
| Generic I/O | Configuration     | input\_\<x\>\_gpio_pin          | int8_t  | GPIO pin                                                      |
| Generic I/O | Configuration     | input\_\<x\>\_debounce_time     | int16_t | Debounce time in ms for input (button) \<x\>                  |
| Generic I/O | Configuration     | input\_\<x\>\_long_press_time   | int16_t | Long press time in ms for input (button) \<x\>                |
| Generic I/O | Configuration     | input\_\<x\>\_type              | int8_t  | Normally Closed (0), Normally Open (1)                        |
| Display     | Configuration     | display\_\<x\>\_gpio_pin\_\<y\> | int8_t  | GPIO pins for display x (\*1)                                 |
| Display     | Configuration     | display\_\<x\>\_type            | uint8_t | Type of display: Driverless 7 Segment Display (0), TM1637 (1) |
| Display     | Configuration     | display\_\<x\>\_brightness      | uint8_t | Brightness                                                    |

\*1
GPIO Pins: when driverless, only 1 segment can be used: y = 0..7 for segment 0 to 7, y = 8: dot.
When using TM1637, the y = 0: CLK, y = 1: DIO.

\*2 - The universe number is not used for this project. It is stored for future expansion to multiple universes, and to demonstrate NVS storage of different data types.

Recommended PSU: 5V 2A — 1509mA headroom.

**Slave code contributed:**

- `slaves/dmx/` — DMX output, named universe NVS storage
- `slaves/display/tm1637/` — seven segment display, brightness via software
- `slaves/input/gpio/` — direct GPIO button / footswitch

**Build order:**

1. Master — verify boot, ESP-NOW init, MAC on serial
2. Input slave — verify heartbeat and button press in master serial
3. Webserver slave — verify status page on phone, slaves shown online
4. Display slave — send test message from webserver, verify on display
5. DMX slave — verify DMX output, universe switching, NVS storage
