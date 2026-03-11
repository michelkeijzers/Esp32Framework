from flask import Flask, request, send_from_directory, jsonify

app = Flask(__name__, static_folder=".")


# Preset names mapping
# Preset names mapping
PRESET_NAMES = {
    "1": "Warm White",
    "2": "Cool Blue",
    "3": "Party Mode",
    "4": "Sunset",
    "5": "Stage Wash",
    "6": "Strobe",
    "7": "Fade",
    "8": "Rainbow",
    "9": "UV",
    "10": "Spotlight",
    "11": "Chase",
    "12": "Pulse",
    "13": "Fire",
    "14": "Ice",
    "15": "Relax",
    "16": "Focus",
    "17": "Energy",
    "18": "Ambient",
    "19": "Accent",
    "20": "Custom Scene",
}

# Example: all presets inactive except the first
PRESET_ACTIVATIONS = [True] + [False] * (len(PRESET_NAMES) - 1)


# GET endpoint to return all preset names and activations as a single array of objects
@app.route("/api/presets", methods=["GET"])
def api_presets():
    names = list(PRESET_NAMES.values())
    activations = PRESET_ACTIVATIONS
    presets = [
        {"name": name, "active": active} for name, active in zip(names, activations)
    ]
    return jsonify(presets)


# --- DMX Preset Actions (stubs, update logic as needed) ---
@app.route("/api/move_preset_up/<int:x>", methods=["POST"])
def move_preset_up(x):
    print(f"Move preset up: {x}")
    # TODO: Implement logic to move preset up
    return api_presets()


@app.route("/api/move_preset_down/<int:x>", methods=["POST"])
def move_preset_down(x):
    print(f"Move preset down: {x}")
    # TODO: Implement logic to move preset down
    return api_presets()


@app.route("/api/delete_preset/<int:x>", methods=["POST"])
def delete_preset(x):
    print(f"Delete preset: {x}")
    # TODO: Implement logic to delete preset
    return api_presets()


@app.route("/api/insert_preset_at/<int:x>", methods=["POST"])
def insert_preset_at(x):
    print(f"Insert preset at: {x}")
    # TODO: Implement logic to insert preset
    return api_presets()


@app.route("/preset_active/<int:x>/<int:state>", methods=["POST"])
def preset_active(x, state):
    print(f"Set preset {x} active: {state}")
    # TODO: Implement logic to set preset active/inactive
    return api_presets()


# Example: all presets inactive except the first
PRESET_ACTIVATIONS = [True] + [False] * (len(PRESET_NAMES) - 1)


@app.route("/api/select_preset/<int:x>", methods=["POST"])
def select_preset(x):
    print(f"/api/select_preset/{x} called")
    preset_name = PRESET_NAMES.get(str(x), str(x))
    return f"<div id='preset-label'>{preset_name}</div>"


@app.route("/api/blackout", methods=["POST"])
def api_blackout():
    print("/api/blackout called")
    return "<div id='preset-label'>Blackout</div>"


@app.route("/")
def index():
    return send_from_directory(".", "index.html")


@app.route("/<path:path>")
def static_files(path):
    return send_from_directory(".", path)


@app.route("/api/send", methods=["POST"])
def api_send():
    print("POST data:", request.form)
    return f"<div id='result'>Received: {request.form.get('dmx-value')}</div>"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
