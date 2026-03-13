
# DMX Controller API Contract

This document describes the API contract between the frontend (web UI) and the backend (Flask server or ESP32 webserver) for the DMX controller project.

# Control Page

## Get Active Preset Numbers

**Endpoint:** `GET /api/active_preset_numbers`  
**Description:** Returns an array of all active preset numbers to display only active presets on the Control page. The backend (Flask or ESP32) provides the current active preset numbers.
**Returns:** `200 OK` with JSON array of preset numbers.
**Website Page:** Control page, when page is opened.

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
**Returns:** `200 OK` with `{ "preset_name": "..." }` on success; `400 Bad Request` on invalid preset.
**Website Page:** Control page, press Preset button.

Example request:

```
POST /api/select_preset/1
```

Example response (JSON):

```json
{ "preset_name": "Warm White" }
```

## Blackout

**Endpoint:** `POST /api/blackout`<br/>
**Description:** Activates blackout mode (all DMX light off). It is a special preset with a fixed name "Blackout".
**Returns:** `200 OK` with `{ "preset_name": "Blackout" }` on success.
**Website Page:** Control page, press Blackout button.

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
**Returns:** `200 OK` with JSON array of presets.
**Website Page:** Presets page, when page is opened.

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
  // ... more presets ...
]
```

## Save Preset

**Endpoint:** `PUT /api/save_preset/<preset_number>`  
**Description:** Saves the current preset (name and DMX values) for the given preset number. Expects the updated preset data in the request body (JSON). Returns ack/nack.
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `400 Bad Request` with `{ "ack": "nok" }` on error.

Example request:

```
PUT /api/save_preset/2

{
  "name": "Cool Blue",
  "dmx_values": [0, 128, 255, ...]
}
```

Example response (JSON):

```json
{ "ack": "ok" }
```

## Move Preset Up

**Endpoint:** `PUT /api/move_preset_up/<preset_index>`  
**Description:** Moves the preset at the given index up by one position. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

Example request:

```
POST /api/move_preset_up/2
```

Example response: See Get Presets example response above, with the specified preset moved up by one position. For example, if "Party Mode" was at index 2 and is moved up, it would swap places with "Cool Blue".

## Move Preset Down

**Endpoint:** `PUT /api/move_preset_down/<preset_index>`  
**Description:** Moves the preset at the given index down by one position. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

Example:

```
POST /api/move_preset_down/1
```

Example response: See Get Preset example response above, with the specified presets move down by one position. For example, if "Warm White" was at index 2 and is moved down, it would swap places with "Party Mode".

## Delete Preset

**Endpoint:** `DELETE /api/delete_preset/<preset_index>`  
**Description:** Deletes the preset at the given index. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

Example:

```
POST /api/delete_preset/2
```

Example response: See Get Preset example response above, with the specified preset being deleted.

## Insert Preset At

**Endpoint:** `PUT /api/insert_preset_at/<preset_index>`  
**Description:** Inserts a new preset at the given index. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index.

Example:

```
POST /api/insert_preset_at/1
```

Example response: See Get Preset example response above, with an empty preset being inserted at the selected position.

## Swap Preset Activation

**Endpoint:** `PUT /api/swap_preset_activation/<preset_index>`<br/>
**Description:** Swaps the preset activation of the preset at the given index. Returns the updated preset list.
**Returns:** `200 OK` with updated preset list; `400 Bad Request` on invalid index or state.

Example request:

```
POST /api/swap_preset_activation/2/1
```

Example response: See Get Preset example response above, with the updated activation state of the preset.

# DMX Edit DMX Value Page

## Preset Value

**Endpoint:** `PUT /api/preset_value/<preset>/<index>/<value>`<br/>
**Description:** Set the DMX value for a specific preset and channel.
**Returns:** `200 OK` with `{ "index": ..., "value": ... }` on success; `400 Bad Request` on invalid input.

Example request:

```
POST /api/preset_value/2/45/128
```

Example response (JSON):

```json
{
  "index": 45,
  "value": 128
}
```

# Configuration Page

## Load Button

**Endpoint:** `GET /api/configuration`<br/>
**Description:** Returns all configuration settings as a JSON object. Used to load configuration in the UI.
**Returns:** `200 OK` with JSON object of config.

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

Example request (URL + JSON):

```json
POST /api/configuration

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

Example request (URL + JSON):

```json
POST /api/configuration_presets_circular_navigation

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
**Returns:** `200 OK` with JSON array of node status.

## Node Status Stream (SSE)

**Endpoint:** `GET /api/status/stream`  
**Description:** Streams real-time node status updates using Server-Sent Events (SSE). Each event contains the latest array of node status objects. Used for live updates on the Status page.
**Returns:** `200 OK` with `Content-Type: text/event-stream` and a stream of JSON arrays. Connection remains open while the page is active.

Example event:

```
event: status
data: [{ "name": "Master", ... }, ...]
```

Example request:

```
GET /api/status
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

Example request:

```
POST /api/reboot
```

Example response:

204 No Content

## Factory Reset

**Endpoint:** `POST /api/factory_reset`<br/>
**Description:** Performs a factory reset on the webserver (clears configuration, resets to defaults, may reboot).<br/>
**Returns:** `200 OK` with `{ "ack": "ok" }` on success; `{ "ack": "nok" }` on failure.<br/>
**Website Page:** Nodes page, press Factory Reset button.

Example request:

```
POST /api/factory_reset
```

Example response (JSON):

```json
{ "ack": "ok" }
```

## Firmware Update 

**Endpoint:**  POST /api/firmware_chunk/{node_idx}
**Description:** Upload a chunk of firmware for a given node (4KB per chunk). The frontend splits the firmware .bin file into 4KB chunks and sends them sequentially. After all chunks are sent, the frontend calls the finalize endpoint to assemble and flash the firmware.
- Request body (JSON):
  - `chunk`: integer, chunk index (starting from 0)
  - `data`: string, base64-encoded binary chunk
- Response (JSON):
  - `{ "ack": "ok" }` on success
  - `{ "ack": "nok", "error": "..." }` on error


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
- Request body: (empty)
- Response (JSON):
  - `{ "ack": "ok" }` on success
  - `{ "ack": "nok", "error": "..." }` on error

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

**Scramble order (index mapping):**

[7, 2, 12, 0, 9, 5, 1, 14, 8, 3, 10, 6, 13, 11, 4, 15]

- To scramble: `scrambled[i] = original[scramble_order[i]]` for i = 0..15
- To descramble: `original[scramble_order[i]] = scrambled[i]` for i = 0..15

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

Example event:

```
data: 2026-03-12 15:42:10
```

Example request:

```
GET /api/logging
```

**Frontend behavior:**
- The Logging page opens a connection to `/api/logging` using EventSource.
- Each received line is appended to a large textarea for live display.
- The connection is closed when the page is unloaded.

# General Notes