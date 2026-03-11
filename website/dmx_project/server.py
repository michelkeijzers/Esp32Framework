# --- Imports ---
from flask import Flask, request, send_from_directory, jsonify
import threading

# --- Flask App ---
app = Flask(__name__, static_folder=".")


# --- Node Status Endpoint ---
@app.route("/api/status", methods=["GET"])
def api_status():
    # Example: 3 nodes with different values
    nodes = [
        {
            "name": "Master",
            "role": "Master",
            "slave_sequence": 1,
            "status_watchdog": "OK",
            "last_communication": "2026-03-11 14:23:01",
            "uptime": "3h 12m",
            "firmware_version": "v1.2.3",
            "config_version": "cfg-2026-03-10",
            "mac_address": "24:6F:28:AA:BB:CC",
            "ip_address": "192.168.1.101",
        },
        {
            "name": "Slave",
            "role": "Slave",
            "slave_sequence": 2,
            "status_watchdog": "ERROR",
            "last_communication": "2026-03-11 14:25:10",
            "uptime": "2h 45m",
            "firmware_version": "v1.2.2",
            "config_version": "cfg-2026-03-09",
            "mac_address": "24:6F:28:DD:EE:FF",
            "ip_address": "192.168.1.102",
        },
        {
            "name": "Backup",
            "role": "Slave",
            "slave_sequence": 3,
            "status_watchdog": "OK",
            "last_communication": "2026-03-11 14:26:30",
            "uptime": "1h 10m",
            "firmware_version": "v1.2.1",
            "config_version": "cfg-2026-03-08",
            "mac_address": "24:6F:28:11:22:33",
            "ip_address": "192.168.1.103",
        },
    ]
    return jsonify(nodes)


# Simple in-memory config for demonstration
CONFIG = {"circular navigation": False}
CONFIG_LOCK = threading.Lock()


# --- New Configuration API Endpoints ---
@app.route("/api/configuration_presets_circular_navigation", methods=["POST"])
def api_config_presets_circular_navigation():
    data = request.get_json(force=True)
    print(
        f"POST /api/configuration_presets_circular_navigation: received state={data.get('state')}"
    )
    if not isinstance(data, dict) or "state" not in data:
        return jsonify({"ack": "nok"}), 400
    with CONFIG_LOCK:
        CONFIG["circular navigation"] = bool(data["state"])
    return jsonify({"ack": "ok"})


# Combined GET and POST for /api/configuration
@app.route("/api/configuration", methods=["GET", "POST"])
def api_configuration():
    if request.method == "GET":
        with CONFIG_LOCK:
            return jsonify(
                {"circular navigation": CONFIG.get("circular navigation", False)}
            )
    elif request.method == "POST":
        data = request.get_json(force=True)
        if not isinstance(data, dict) or "circular navigation" not in data:
            return jsonify({"ack": "nok"}), 400
        with CONFIG_LOCK:
            CONFIG["circular navigation"] = bool(data["circular navigation"])
        return jsonify({"ack": "ok"})


# --- Configuration Endpoints ---
@app.route("/api/load_config", methods=["POST"])
def api_load_config():
    print("POST /api/load_config")
    with CONFIG_LOCK:
        return jsonify(
            {"circular navigation": CONFIG.get("circular navigation", False)}
        )


@app.route("/api/save_config", methods=["POST"])
def api_save_config():
    print("POST /api/save_config")
    data = request.get_json(force=True)
    if not isinstance(data, dict) or "circular navigation" not in data:
        return jsonify({"ack": "nok"}), 400
    with CONFIG_LOCK:
        CONFIG["circular navigation"] = bool(data["circular navigation"])
    return jsonify({"ack": "ok"})


@app.route("/api/get_preset_values/<int:x>", methods=["GET"])
def get_preset_values(x):
    print(f"GET /api/get_preset_values/{x}")
    # TODO: Replace with real preset data lookup
    # For now, return a dummy array with some nonzero values for demonstration
    values = [0] * 512
    if 1 <= x <= 20:
        # Example: set some values for demonstration
        values[0] = 134
        values[1] = 34
        values[2] = 68
        values[3] = 128
        values[10] = 255
        values[100] = 77
    return jsonify(values)


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


@app.route("/api/presets", methods=["GET"])
def api_presets():
    print("GET /api/presets")
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
    return api_presets()


@app.route("/api/insert_preset_at/<int:x>", methods=["POST"])
def insert_preset_at(x):
    print(f"Insert preset at: {x}")
    return api_presets()


@app.route("/api/swap_preset_activation/<int:x>/<int:state>", methods=["POST"])
def preset_swap_active(x, state):
    print(f"Swap preset activation {x} to {state}")
    # TODO: Update PRESET_ACTIVATIONS[x-1] = bool(state)
    return api_presets()


# Endpoint to set a DMX value for a preset
@app.route("/api/preset_value/<int:preset>/<int:index>/<int:value>", methods=["POST"])
def set_preset_value(preset, index, value):
    # TODO: Implement logic to update the DMX value for the given preset and index
    print(f"Set DMX value: preset={preset}, index={index}, value={value}")
    return jsonify({"index": index, "value": value})


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


@app.route("/", methods=["GET"])
def index():
    print("GET /")
    return send_from_directory(".", "index.html")


@app.route("/<path:path>", methods=["GET"])
def static_files(path):
    print(f"GET /{path}")
    return send_from_directory(".", path)


@app.route("/api/send", methods=["POST"])
def api_send():
    print("POST data:", request.form)
    return f"<div id='result'>Received: {request.form.get('dmx-value')}</div>"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
