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

Example response (JSON):

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

Example response (JSON):

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

Example response (JSON):

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

Example response: See Get Preset example response above, with the specified presets move down by one position. For example, if "Warm White" was at index 2 and is moved down, it would swap places with "Party Mode".

## Delete Preset

**Endpoint:** `POST /api/delete_preset/<preset_index>`  
**Description:** Deletes the preset at the given index. Returns the updated preset list.

Example:

```
POST /api/delete_preset/2
```

Example response: See Get Preset example response above, with the specified preset being deleted.

## Insert Preset At

**Endpoint:** `POST /api/insert_preset_at/<preset_index>`  
**Description:** Inserts a new preset at the given index. Returns the updated preset list.

Example:

```
POST /api/insert_preset_at/1
```

Example response: See Get Preset example response above, with an empty preset being inserted at the selected position.

## Swap Preset Activation

**Endpoint:** `POST /api/swap_preset_activation/<preset_index>`<br/>
**Description:** Swaps the preset activation of the preset at the given index. Returns the updated preset list.

Example request:

```
POST /api/swap_preset_activation/2/1
```

Example response: See Get Preset example response above, with the updated activation state of the preset.

# DMX Edit DMX Value Page

## Preset Value

**Endpoint:** `POST /api/preset_value/<preset>/<index>/<value>`<br/>
**Description:** Set the DMX value for a specific preset and channel.

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

**Endpoint:** `POST /api/configuration`<br/>
**Description:** Saves all configuration settings. Expects a JSON object with all config fields. Returns ack ("ok"/"nok").

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

**Endpoint:** `POST /api/configuration_presets_circular_navigation`<br/>
**Description:** Sets the circular navigation boolean for presets. Expects `{ "state": true|false }` in the request body. Returns ack/nack.

Example request (URL + JSON):

```json
POST /api/configuration_presets_circular_navigation

{ "state": true }
```

Example response (JSON):

```json
{ "ack": "ok" }
```

# General Notes

- All API endpoints are under the `/api/` prefix.
- For production/embedded (ESP32) use, all responses should be JSON unless otherwise noted.
- Extend this contract as new features/endpoints are added.
