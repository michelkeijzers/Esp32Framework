from flask import Flask, request, send_from_directory

app = Flask(__name__, static_folder=".")

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
