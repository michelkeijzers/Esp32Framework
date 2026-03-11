# DMX Controller API Contract

This document describes the API contract between the frontend (web UI) and the backend (Flask server or ESP32 webserver) for the DMX controller project.

# Control Page

## Select Preset

**Endpoint:** `POST /api/select_preset/<preset_number>`<br/>
**Description:** Selects a DMX preset by number (1-20). The backend will look up the preset name and return it.
**Website Page:** Control page, press Preset button.

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
**Website Page:** Control page, press Blackout button.

Example request:

```
POST /api/blackout
```

Example response:

```json
{ "preset_name": "Blackout" }
```

# DMX Presets Page

# Get Presets

**Endpoint:** `GET /api/presets`  
**Description:** Returns an array of all DMX presets with their names and active states to display the full Presets list. The backend (Flask or ESP32) provides the current names and activation status.
**Website Page:** Presets page, when page is opened.

Example request:

```
GET /api/presets
```

Example response:

```json
[
  { "name": "Warm White", "active": true },
  { "name": "Cool Blue", "active": false },
  { "name": "Party Mode", "active": false }
  // ... more presets ...
]
```

## Move Preset Up

**Endpoint:** `POST /api/move_preset_up/<preset_index>`  
**Description:** Moves the preset at the given index up by one position. Returns the updated preset list.

Example request:

```
POST /api/move_preset_up/2
```

Example response: See Get Presets example response above, with the specified preset moved up by one position. For example, if "Party Mode" was at index 2 and is moved up, it would swap places with "Cool Blue".

## Move Preset Down

**Endpoint:** `POST /api/move_preset_down/<preset_index>`  
**Description:** Moves the preset at the given index down by one position. Returns the updated preset list.

Example: 

```
POST /api/move_preset_down/1
```
Response: See Get Preset example response above, with the specified presets move down by one position. For example, if "Warm White" was at index 2 and is moved down, it would swap places with "Party Mode".

## Delete Preset

**Endpoint:** `POST /api/delete_preset/<preset_index>`  
**Description:** Deletes the preset at the given index. Returns the updated preset list.

Example:

```
POST /api/delete_preset/2
```

## Insert Preset At

**Endpoint:** `POST /api/insert_preset_at/<preset_index>`  
**Description:** Inserts a new preset at the given index. Returns the updated preset list.

Example request:

```
POST /api/insert_preset_at/1
```

## Set Preset Active

**Endpoint:** `POST /preset_active/<preset_index>/<state>`  
**Description:** Sets the active state of the preset at the given index. Returns the updated preset list. `state` is 1 for active, 0 for inactive.

Example:

```
POST /api/preset_activate/2/1
Response: See Get Preset example response above, with the updated activation state of the preset.
```

# General Notes

- All API endpoints are under the `/api/` prefix.
- For production/embedded (ESP32) use, all responses should be JSON unless otherwise noted.
- Extend this contract as new features/endpoints are added.
```

# DMX Edit DMX Value Page

## Preset Value

**Endpoint:** `POST /api/preset_value/<preset>/<index>/<value>`
**Description:** Set the DMX value for a specific preset and channel.

Example request: 

```
POST /api/preset_value/2/45/128
Response:
{
  "status": "ok",
  "preset": 2,
  "index": 45,
  "value": 128
}
```

---

Add this to your API documentation as the contract for updating a DMX value via POST.
