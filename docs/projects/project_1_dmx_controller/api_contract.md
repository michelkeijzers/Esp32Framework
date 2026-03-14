# DMX Controller API Contract

This document describes the API contract between the frontend (web UI) and the backend (Flask server or ESP32 webserver) for the DMX controller project.

# Table of Contents

- [Control Page](#control-page)
  - [Get Active Preset Numbers](#get-active-preset-numbers)
  - [Select Preset](#select-preset)
  - [Blackout](#blackout)
- [DMX Presets Page](#dmx-presets-page)
  - [Get Presets](#get-presets)   
  - [Save Preset](#save-preset)
  - [Move Preset Up](#move-preset-up)
  - [Move Preset Down](#move-preset-down)
  - [Delete Preset](#delete-preset) 
  - [Insert Preset At](#insert-preset-at)
  - [Swap Preset Activation](#swap-preset-activation)
- [Edit Preset](#edit-preset)
  - [Preset Values](#preset-values)
- [Edit Value Page](#edit-value-page)
  - [Preset Value](#preset-value) 
- [Configuration Page](#configuration-page)
  - [Load Button](#load-button) 
  - [Save Button](#save-button)
  - [Presets/Circular Navigation Checkbox](#presetscircular-navigation-checkbox)
- [Status Page](#status-page)
  - [Get Node Status](#get-node-status) 
  - [Node Status Stream (SSE)](#node-status-stream-sse)
- [Nodes Page](#nodes-page)
  - [Opening page](#opening-page)
  - [Save Button](#save-button-1)
  - [Reboot Button](#reboot-button)
  - [Factory Reset](#factory-reset)
  - [Firmware Update](#firmware-update)
- [Security Page](#security-page)
  - [Send ESP-NOW Security Key](#send-esp-now-security-key) 
  - [Send Wi-Fi Password](#send-wi-fi-password)
- [Logging Page](#logging-page)
  - [Logging Stream (SSE)](#logging-stream-sse) 


# Control Page

## Get Active Preset Numbers

**Endpoint:** `GET /api/active_preset_numbers`  
**Description:** Returns an array of all active preset numbers to display only active presets on the Control page. The backend (Flask or ESP32) provides the current active preset numbers.
**Returns:** `200 OK` with JSON array of preset numbers.
**Website Page:** Control page, when page is opened.

**Request Specification:**
No request parameters or body required.

**Response Specification:**
Array of integers representing active preset numbers:
- Each element (integer, required) – Preset number (1-20) that is currently active

Example request:

```
GET /api/active_preset_numbers
```

Example response (JSON):

```json
[1, 2, 5, 7, 10, 12, 15, 18, 20]
```

## Select Preset

**Endpoint:** `POST /api/select_preset/<preset_number>`<br/>
**Description:** Selects a DMX preset by number (1-20). The backend will look up the preset name and return it.
**Returns:** `200 OK` with JSON response containing the selected preset name; `400 Bad Request` on invalid preset (preset_number not in 1-20 range).
**Website Page:** Control page, press Preset button.

**Request Specification:**
- **URL Parameter:** `preset_number` (required, integer 1-20)

**Response Specification:**
- `preset_name` (string, required) – Name of the selected preset (e.g., "Warm White")

Example request:

```
POST /api/select_preset/1
```

Example response:

```json
{ "preset_name": "Warm White" }
```

## Blackout

**Endpoint:** `POST /api/blackout`<br/>
**Description:** Activates blackout mode (all DMX light off). It is a special preset with a fixed name "Blackout".
**Returns:** `200 OK` with `{ "preset_name": "Blackout" }` on success.
**Website Page:** Control page, press Blackout button.

**Request Specification:**
No request body required.

**Response Specification:**
- `preset_name` (string, required) – Name of the blackout preset (always "Blackout")

Example request:

```
POST /api/blackout
```

Example response (JSON):

```json
{ "preset_name": "Blackout" }
```

# DMX Presets Page

# Get Presets

**Endpoint:** `GET /api/presets`  
**Description:** Returns an array of all DMX presets with their names and active states to display the full Presets list. The backend (Flask or ESP32) provides the current names and activation status.
**Returns:** `200 OK` with JSON array of preset objects.
**Website Page:** Presets page, when page is opened.

**Response Specification:**
Array of preset objects, each containing:
- `name` (string, required) – Name of the preset (e.g., "Warm White")
- `active` (boolean, required) – Whether the preset is currently active

Example request:

```
GET /api/presets
```

Example response (JSON):

```json
[
  { "name": "Warm White", "active": true },
  { "name": "Cool Blue", "active": false },
  { "name": "Party Mode", "active": false }
]
```

## Save Preset

**Endpoint:** `PUT /api/save_preset/<preset_number>`  
**Description:** Saves the current preset (name and DMX values) for the given preset number. Expects the updated preset data in the request body (JSON). Returns ack/nack.
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `400 Bad Request` with `{ "ack": "nok" }` on error.

**Request Specification:**
- **URL Parameter:** `preset_number` (required, integer 1-20)
- **Body:** JSON object containing:
  - `name` (string, required) – Name of the preset (e.g., "Cool Blue")
  - `dmx_values` (array of integers, required) – Array of 512 DMX channel values (0–255)

**Response Specification:**
- `ack` (string, required) – "ok" on success, "nok" on failure

Example request:

```
PUT /api/save_preset/2

{
  "name": "Cool Blue",
  "dmx_values": [0, 128, 255, 0, 0, ..., 0]
}
```

Example response (JSON):

```json
{ "ack": "ok" }
```

## Move Preset Up

**Endpoint:** `PUT /api/presets/<preset_index>/move_up`  
**Description:** Moves the preset at the given index up by one position. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

**Request Specification:**
- **URL Parameter:** `preset_index` (required, integer 0-based index)

**Response Specification:**
Array of preset objects (same as Get Presets) with presets reordered after the move.

Example request:

```
PUT /api/presets/2/move_up
```

Example response (JSON):

```json
[
  { "name": "Warm White", "active": true },
  { "name": "Party Mode", "active": false },
  { "name": "Cool Blue", "active": false }
]
```

## Move Preset Down

**Endpoint:** `PUT /api/presets/<preset_index>/move_down`  
**Description:** Moves the preset at the given index down by one position. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

**Request Specification:**
- **URL Parameter:** `preset_index` (required, integer 0-based index)

**Response Specification:**
Array of preset objects (same as Get Presets) with presets reordered after the move.

Example request:

```
PUT /api/presets/1/move_down
```

Example response (JSON):

```json
[
  { "name": "Warm White", "active": true },
  { "name": "Party Mode", "active": false },
  { "name": "Cool Blue", "active": false }
]
```

## Delete Preset

**Endpoint:** `DELETE /api/presets/<preset_index>`  
**Description:** Deletes the preset at the given index. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

**Request Specification:**
- **URL Parameter:** `preset_index` (required, integer 0-based index)

**Response Specification:**
Array of preset objects (same as Get Presets) with the specified preset removed.

Example request:

```
DELETE /api/presets/2
```

Example response (JSON):

```json
[
  { "name": "Warm White", "active": true },
  { "name": "Cool Blue", "active": false }
]
```

## Insert Preset At

**Endpoint:** `POST /api/presets/<preset_index>/insert_at`  
**Description:** Inserts a new preset at the given index. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

**Request Specification:**
- **URL Parameter:** `preset_index` (required, integer 0-based index)
- **Body:** JSON object containing:
  - `name` (string, optional) – Name of the new preset (default: empty string)
  - `dmx_values` (array of integers, optional) – DMX values for new preset (default: all zeros)

**Response Specification:**
Array of preset objects (same as Get Presets) with the new preset inserted at the specified index.

Example request:

```json
POST /api/presets/1/insert_at

{
  "name": "New Preset",
  "dmx_values": [0, 0, 0, ..., 0]
}
```

Example response (JSON):

```json
[
  { "name": "Warm White", "active": true },
  { "name": "New Preset", "active": false },
  { "name": "Cool Blue", "active": false },
  { "name": "Party Mode", "active": false }
]
```

## Swap Preset Activation

**Endpoint:** `PUT /api/presets/<preset_index>/swap_activation`<br/>
**Description:** Toggles the activation state of the preset at the given index. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

**Request Specification:**
- **URL Parameter:** `preset_index` (required, integer 0-based index)

**Response Specification:**
Array of preset objects (same as Get Presets) with the activation state of the specified preset toggled.

Example request:

```
PUT /api/presets/2/swap_activation
```

Example response (JSON):

```json
[
  { "name": "Warm White", "active": true },
  { "name": "Cool Blue", "active": false },
  { "name": "Party Mode", "active": true }
]
```

# Edit Preset

## Preset Values

**Endpoint:** `GET /api/preset_values/<preset_number>`<br/>
**Description:** Returns an array of 512 DMX values (0–255) for the specified preset number. Used to display or edit all DMX channel values for a given preset in the frontend.<br/>
**Returns:** `200 OK` with JSON array of DMX values if preset exists; `400 Bad Request` if preset not found.

**Request Specification:**
- **URL Parameter:** `preset_number` (required, integer 1-20)

**Response Specification:**
Array of 512 integers (0-255), where each element represents a DMX channel value:
- Index 0-511 represents DMX channels 1-512
- Each value is an integer 0-255 representing the intensity/brightness

**Example request:**
```
GET /api/preset_values/2
```

**Example response:**
```json
[0, 128, 255, 0, 0, 64, 192, ..., 0]
```

# Edit Value Page

## Preset Value

**Endpoint:** `PUT /api/preset_value/<preset>/<index>/<value>`<br/>
**Description:** Sets the DMX value for a specific preset and channel.
**Returns:** `200 OK` with updated value object on success; `400 Bad Request` on invalid input (out of range values or invalid preset).

**Request Specification:**
- **URL Parameters:**
  - `preset` (required, integer 1-20) – Preset number
  - `index` (required, integer 0-511) – DMX channel index (0-based, 512 total channels)
  - `value` (required, integer 0-255) – DMX intensity value

**Response Specification:**
- `index` (integer, required) – The DMX channel index that was updated
- `value` (integer, required) – The new DMX value (0-255)
- `preset` (integer, required) – The preset number

Example request:

```
PUT /api/preset_value/2/45/128
```

Example response (JSON):

```json
{
  "preset": 2,
  "index": 45,
  "value": 128
}
```

# Configuration Page

## Load Button

**Endpoint:** `GET /api/configuration`<br/>
**Description:** Returns all configuration settings as a JSON object. Used to load configuration in the UI.
**Returns:** `200 OK` with JSON object of config.

**Response Specification:**
JSON object containing all configuration settings:
- `circular navigation` (boolean, required) – Enable/disable circular navigation for preset lists

Example request:

```
GET /api/configuration
```

Example response (JSON):

```json
{
  "circular navigation": true
}
```

## Save Button

**Endpoint:** `PUT /api/configuration`<br/>
**Description:** Saves all configuration settings. Expects a JSON object with all config fields. Returns ack ("ok"/"nok").
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `400 Bad Request` with `{ "ack": "nok" }` on error.

**Request Specification:**
JSON object containing configuration fields to save:
- `circular navigation` (boolean, required) – Enable/disable circular navigation for preset lists

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)

Example request (URL + JSON):

```json
PUT /api/configuration

{
  "circular navigation": false
}
```

Example response (JSON):

```json
{ "ack": "ok" }
```

## Presets/Circular Navigation Checkbox

**Endpoint:** `PUT /api/configuration_presets_circular_navigation`<br/>
**Description:** Sets the circular navigation boolean for presets. Expects `{ "state": true|false }` in the request body. Returns ack/nack.
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `400 Bad Request` with `{ "ack": "nok" }` on error.

**Request Specification:**
JSON object containing the circular navigation state:
- `state` (boolean, required) – Enable (true) or disable (false) circular navigation

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)

Example request (URL + JSON):

```json
PUT /api/configuration_presets_circular_navigation

{ "state": true }
```

Example response (JSON):

```json
{ "ack": "ok" }
```


# Status Page

## Get Node Status

**Endpoint:** `GET /api/status`  
**Description:** Returns an array of all ESP32 nodes with their current status and metadata. Used to display the status dashboard in the web UI.
**Returns:** `200 OK` with JSON array of node status objects.

**Response Specification:**
Array of node objects, each containing:
- `name` (string, required) – Node identifier (e.g., "Master", "Slave")
- `role` (string, required) – Role of the node (e.g., "Master", "Slave")
- `slave_type` (string, required) – Type of slave (e.g., "Webserver", "DMX", "MIDI")
- `slave_sequence` (integer, required) – Sequence number of the slave (1-based)
- `status_watchdog` (string, required) – Watchdog status (e.g., "OK", "ERROR", "TIMEOUT")
- `last_communication` (string, required) – ISO 8601 timestamp of last communication
- `uptime` (string, required) – Human-readable uptime (e.g., "3h 12m")
- `firmware_version` (string, required) – Version string (e.g., "v1.2.3")
- `config_version` (string, required) – Configuration version (e.g., "cfg-2026-03-10")
- `mac_address` (string, required) – MAC address in format XX:XX:XX:XX:XX:XX
- `ip_address` (string, required) – IPv4 address (e.g., "192.168.1.101")

## Node Status Stream (SSE)

**Endpoint:** `GET /api/status/stream`  
**Description:** Streams real-time node status updates using Server-Sent Events (SSE). Each event contains the latest array of node status objects. Used for live updates on the Status page.
**Returns:** `200 OK` with `Content-Type: text/event-stream` and a stream of JSON arrays. Connection remains open while the page is active.

**Response Specification:**
Server-sent events (one per update) containing an array of node objects (same structure as Get Node Status endpoint). Each event includes:
- `event` (string) – Event type identifier ("status")
- `data` (JSON array) – Array of node status objects

Example request:

```
GET /api/status/stream
```

Example event:

```
event: status
data: [{ "name": "Master", "role": "Master", "slave_type": "Webserver", "slave_sequence": 1, "status_watchdog": "OK", "last_communication": "2026-03-11 14:23:01", "uptime": "3h 12m", "firmware_version": "v1.2.3", "config_version": "cfg-2026-03-10", "mac_address": "24:6F:28:AA:BB:CC", "ip_address": "192.168.1.101" }, { "name": "Slave", "role": "Slave", "slave_type": "DMX", "slave_sequence": 2, "status_watchdog": "ERROR", "last_communication": "2026-03-11 14:25:10", "uptime": "2h 45m", "firmware_version": "v1.2.2", "config_version": "cfg-2026-03-09", "mac_address": "24:6F:28:DD:EE:FF", "ip_address": "192.168.1.102" }]
```

Example response (JSON):

```json
[
  {
    "name": "Master",
    "role": "Master",
    "slave_type": "Webserver",
    "slave_sequence": 1,
    "status_watchdog": "OK",
    "last_communication": "2026-03-11 14:23:01",
    "uptime": "3h 12m",
    "firmware_version": "v1.2.3",
    "config_version": "cfg-2026-03-10",
    "mac_address": "24:6F:28:AA:BB:CC",
    "ip_address": "192.168.1.101"
  },
  {
    "name": "Slave",
    "role": "Slave",
    "slave_type": "DMX",
    "slave_sequence": 2,
    "status_watchdog": "ERROR",
    "last_communication": "2026-03-11 14:25:10",
    "uptime": "2h 45m",
    "firmware_version": "v1.2.2",
    "config_version": "cfg-2026-03-09",
    "mac_address": "24:6F:28:DD:EE:FF",
    "ip_address": "192.168.1.102"
  },
]
# Node object fields:
Each node object contains:
  - name: string
  - role: string
  - slave_type: string (e.g. "Webserver", "DMX", "MIDI")
  - slave_sequence: integer
  - status_watchdog: string
  - last_communication: string
  - uptime: string
  - firmware_version: string
  - config_version: string
  - mac_address: string
  - ip_address: string
```

# Nodes Page

## Opening page

**Endpoint:** `GET /api/nodes_info`  
**Description:** Returns an array of all nodes with their names and current MAC addresses. Used to display and edit node MACs in the Initialization page.
**Returns:** `200 OK` with JSON array of nodes.

**Response Specification:**
Array of node objects, each containing:
- `name` (string, required) – Node identifier (e.g., "Master", "Webserver")
- `mac_address` (string, required) – MAC address in format XX:XX:XX:XX:XX:XX

Example request:

```
GET /api/nodes_info
```

Example response (JSON):

```json
[
  { "name": "Master", "mac_address": "24:6F:28:AA:BB:CC" },
  { "name": "Webserver", "mac_address": "24:6F:28:BB:CC:DD" },
  { "name": "GPIO Slave", "mac_address": "24:6F:28:CC:DD:EE" },
  { "name": "Display Slave", "mac_address": "24:6F:28:DD:EE:FF" }
]
```

## Save Button

**Endpoint:** `POST /api/nodes_info`  
**Description:** Updates the MAC addresses for all nodes. Expects a JSON array of MAC addresses (in the same order as returned by GET). Returns ack/nack. Only valid MAC addresses are accepted.
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `400 Bad Request` with `{ "ack": "nok" }` on error.

**Request Specification:**
Array of MAC address strings (one per node, in the same order as GET /api/nodes_info):
- Each element (string, required) – MAC address in format XX:XX:XX:XX:XX:XX

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)

Example request:

```json
POST /api/nodes_info

["24:6F:28:AA:BB:CC", "24:6F:28:BB:CC:DD", "24:6F:28:CC:DD:EE", "24:6F:28:DD:EE:FF"]
```

Example response (JSON):

```json
{ "ack": "ok" }
```

## Reboot Button

**Endpoint:** `POST /api/reboot`  
**Description:** Triggers a system reboot action. No request body or response is required. Used by the Reboot button on the Initialization page.
**Returns:** `204 No Content` on success.

**Request Specification:**
No request body required.

**Response Specification:**
No response body. HTTP status 204 No Content indicates success.

Example request:

```
POST /api/reboot
```

Example response:

```
204 No Content
```

## Factory Reset

**Endpoint:** `POST /api/factory_reset`<br/>
**Description:** Performs a factory reset on the webserver (clears configuration, resets to defaults, may reboot).<br/>
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `{ "ack": "nok" }` on failure.<br/>
**Website Page:** Nodes page, press Factory Reset button.

**Request Specification:**
No request body required.

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)

Example request:

```
POST /api/factory_reset
```

Example response (JSON):

```json
{ "ack": "ok" }
```

## Firmware Update 

### POST /api/firmware_chunk/{node_idx}

**Endpoint:** `POST /api/firmware_chunk/{node_idx}`  
**Description:** Upload a chunk of firmware for a given node (4KB per chunk). The frontend splits the firmware .bin file into 4KB chunks and sends them sequentially. After all chunks are sent, the frontend calls the finalize endpoint to assemble and flash the firmware.

**Request Specification:**
- **URL Parameter:** `node_idx` (required, integer) – Node index
- **Body:** JSON object containing:
  - `chunk` (integer, required) – Chunk index (starting from 0)
  - `data` (string, required) – Base64-encoded binary chunk data

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)
- `error` (string, optional) – Error message if ack is "nok"

**Upload Process:**
1. User selects .bin file in the Nodes page UI. JavaScript splits the file into 4KB chunks.
2. For each chunk, POST to `/api/firmware_chunk/{node_idx}` with chunk index and base64 data. No checksum is used; TCP ensures integrity.
3. The UI handles retries for failed chunks and shows a live progress bar.
4. After all chunks, POST to `/api/firmware_finish/{node_idx}`.
5. On success, the UI shows "Firmware updated!" for that node.

**Note:** During firmware upload, the frontend buffers live status updates (SSE) to prevent UI re-renders from interrupting the progress bar and button state. The latest status is rendered after upload completes.

Example request:
```json
POST /api/firmware_chunk/1

{
  "chunk": 0,
  "data": "base64-encoded-chunk-data..."
}
```

Example response (JSON):

```json
{ "ack": "ok" }
```

### POST /api/firmware_finish/{node_idx}

**Endpoint:** `POST /api/firmware_finish/{node_idx}`  
**Description:** Finalize firmware upload for a node, assemble and flash firmware.

**Request Specification:**
- **URL Parameter:** `node_idx` (required, integer) – Node index
- **Body:** (empty, no request body required)

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)
- `error` (string, optional) – Error message if ack is "nok"

Example request:

```
POST /api/firmware_finish/1
```

Example response (JSON):

```json
{ "ack": "ok" }
```

# Security Page

## Send ESP-NOW Security Key

**Endpoint:** `POST /api/esp_now_key`  
**Description:** Sends the ESP-NOW security key from the web UI to the backend. The key is a 16-byte (uint8_t) array, scrambled using a fixed permutation for security and reversibility. The backend must descramble the key using the same order.
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `400 Bad Request` with `{ "ack": "nok" }` on error.

**Request Specification:**
- **Body:** JSON array of 16 hex strings representing scrambled key bytes:
  - Each element (string, required) – Hex string (e.g., "a1", "b2") representing a key byte
  - Scramble order (index mapping): [7, 2, 12, 0, 9, 5, 1, 14, 8, 3, 10, 6, 13, 11, 4, 15]
  - To descramble: `original[scramble_order[i]] = scrambled[i]` for i = 0..15

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)

Example request (URL + JSON):

```json
POST /api/esp_now_key

["a1", "b2", "c3", "d4", "e5", "f6", "07", "18", "29", "3a", "4b", "5c", "6d", "7e", "8f", "90"]
```

**Response (JSON):**

```json
{"ack": "ok"}
```

## Send Wi-Fi Password

**Endpoint:** `POST /api/wifi_password`  
**Description:** Sends the Wi-Fi password from the web UI to the backend. The password is a string (WPA2: 8-63 characters). The backend must validate and securely store or forward the password.
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `400 Bad Request` with `{ "ack": "nok" }` on error.

**Request Specification:**
- **Body:** JSON object containing:
  - `password` (string, required) – Wi-Fi password (WPA2: 8-63 characters)

**Response Specification:**
- `ack` (string, required) – Acknowledgment status ("ok" on success, "nok" on failure)

Example request (URL + JSON):

```json
POST /api/wifi_password

{ "password": "mysecretwifi" }
```

**Response (JSON):**

```json
{"ack": "ok"}
```


# Logging Page

## Logging Stream (SSE)

**Endpoint:** `GET /api/logging`  
**Description:** Streams real-time log lines using Server-Sent Events (SSE). 
**Returns:** `200 OK` with `Content-Type: text/event-stream` and a stream of log lines. Connection remains open while the page is active.

**Request Specification:**
No request parameters or body required.

**Response Specification:**
Server-sent events containing individual log lines:
- `event` (string) – Event type ("") (default event type for plain text)
- `data` (string) – Log line containing timestamp and message (e.g., "2026-03-12 15:42:10 [INFO] System initialized")

**Frontend behavior:**
- The Logging page opens a connection to `/api/logging` using EventSource.
- Each received line is appended to a large textarea for live display.
- The connection is closed when the page is unloaded.

Example request:

```
GET /api/logging
```

Example event:

```
data: 2026-03-12 15:42:10 [INFO] System initialized
data: 2026-03-12 15:42:11 [DEBUG] WebServer started
data: 2026-03-12 15:42:12 [INFO] All nodes connected
```

# General Notes