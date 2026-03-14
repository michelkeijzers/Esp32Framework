# Compiler issues

# VS Code

# IDF Terminal

- Ctrl-Shift-P, select "ESP-IDF Terminal"

## Intellisense include issues (red underlines under #include)

- Ctrl-Shift-P, select "ESP-IDF Terminal"
- In terminal, type: idf.py build

Check c_cpp_properties.json :

```
      "includePath": [
        "${workspaceFolder}/**",
        "C:
        "C:/Users/i4studio/esp/v5.4.1/esp-idf/components/**/include",
        "C:/Users/i4studio/esp/v5.4.1/esp-idf/components/freertos/**",

      ],
```

Still did not work, so I disabled the squiggle warnings.

# Website

## Android connection

Using Htmx and pico.min.css
in website/dmx_project folder:

pip install flask

python server.py --host=0.0.0.0 --port=8000

website local: 192.168.1.254:8080

check firewall setting:

- Open Windows Defender Firewall settings on your PC.
- Go to “Advanced settings” > “Inbound Rules.”
- Add a new rule:
  Rule type: Port
  Protocol: TCP
  Port: 8080
  Allow the connection
- Apply to all profiles (Domain, Private, Public)
- Name: “Flask Web Server 8080” (or similar)
- Save and restart your Flask server if needed.

# ESP32 Build and API Tester Shortcut

You can build the ESP32 project and run the API tester with a single shortcut key:

**Press F8** to:
- Build the ESP32 project (same as clicking the wrench button or pressing Ctrl+E, B with the ESP-IDF extension)
- Build and run the API tester in `tests/api_tester` (runs `cmake --build build && .\build\Debug\api_tester.exe`)

Alternatively, you can use `Ctrl+Shift+B` (or open the Command Palette and select `Run Build Task...`) and choose **ESP32: Build All + Run API Tester** from the task list.

The keybinding is defined in `.vscode/keybindings.json` and the tasks are in `.vscode/tasks.json`.

