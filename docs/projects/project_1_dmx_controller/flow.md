# FLOW

## INIT

| From     | To       | Message         |
| -------- | -------- | --------------- |
| DC.Main  | IO.Main  | SetRouting      |
| DC.Http  | DC.Main  | GetPresetNames  |
| DC.Main  | DMX.Main | GetPresetNames  |
| DMX.Main | DMX.Fs   | ReadPresetNames |
| DMX.Fs   | Dmx.Main | PresetNames     |
| Dmx.Main | DC.Main  | PresetNames     |
| DC.Main  | DC.Http  | PresetNames     |

## Edit Preset Name

| From     | To       | Message       |
| -------- | -------- | ------------- |
| DC.http  | DC.Main  | SetPresetName |
| DC.Main  | DMX.Main | SetPresetName |
| DMX.Main | DMX.Fs   | SetPresetName |
| Ack      |          |               |

# Set Preset Value

As Edit Preset Name

# Select Next Preset (via foot switch)

| From          | To       | Message          |
| ------------- | -------- | ---------------- |
| IO.Main       | DC.Main  | IoChanged        |
| DC.Main       | DMX.Main | SetCurrentPreset |
| DMX.Main      | DMX.Fs   | ReadPreset       |
| Dmx.Fs        | DMX.Main | PresetData       |
| DMX.Main      | DMX.Max  | SendDmx          |
| Send to Http? |          |                  |
