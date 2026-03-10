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
