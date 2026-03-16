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

# LittleFS & Web UI Deployment

## Overview
The ESP32 webserver serves a web UI stored in LittleFS (1 MB partition). The build process automatically bundles and minifies the website using Vite, then packages it into the LittleFS image during the ESP32 build.

## Partition Layout
The ESP32-C3 4 MB flash is divided as:
- **NVS**: 100 KB (config storage)
- **App (Factory)**: 1 MB (main firmware)
- **OTA**: 1 MB (2nd firmware for OTA updates)
- **LittleFS**: 512 KB (web UI and static assets)

## Building & Deploying the Website

### Step 1: Setup Vite (One-time)
In the `website/dmx_project/` folder:
```bash
cd website/dmx_project
npm install
```

### Step 2: Build the Website (Before Each Firmware Flash)
```bash
npm run build
```
This creates an optimized `dist/` folder with minified HTML, CSS, and JS.

### Step 3: Create LittleFS Image
```bash
python create_littlefs_image.py
```
This generates `littlefs_image.bin` from the `dist/` folder.

### Step 4: Flash to ESP32
Flash the ESP32 with both firmware and LittleFS:
```bash
idf.py -p PORT flash
```

If you only want to flash the website (no firmware update):
```bash
esptool.py -p PORT write_flash 0x230000 website/dmx_project/littlefs_image.bin
```
(0x230000 is the LittleFS partition offset from partitions.csv)

### Step 5: Local Testing (Optional)
Before flashing, test the built website locally:
```bash
cd website/dmx_project
npm run preview
```
This serves the `dist/` folder on http://localhost:5173. Verify all pages load and API calls work correctly.

## Technical Details

### Static File Handler
- Registered in `Webserver.cpp` as a catch-all URI handler (`/*`)
- Automatically serves `index.html` for root path and non-API routes (SPA support)
- Sets correct MIME types using `StaticFileHandler::get_mime_type()`
- Returns 404 if file not found

### LittleFS Mounting
- Mounted at startup in `Webserver::mount_littlefs()`
- Partition label: `littlefs`, base path: `/littlefs`
- Auto-formats partition if mount fails (graceful degradation)

### API / Static Priority
- All API endpoints (`/api/v1/*`) are registered **before** the static file handler
- Ensures API calls route to C++ handlers, never to the filesystem

## Troubleshooting

- **Website not loading**: Check if LittleFS is mounted (see serial logs)
- **Old files still showing**: Ensure `npm run build` completes before flashing
- **LittleFS out of space**: Check website size with `du -sh website/dmx_project/dist/`

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



### Used Tools etc

**Languages:** 

- C++ for ESP32 firmware
- Python for server and build scripts
- HTML/CSS/JS for web UI

**Tools:**

- Vite for web UI bundling and minification
- CMake for ESP32 build system
- ESP-IDF for ESP32 development
- Postman for API testing
- Visual Studio Code with ESP-IDF extension for development
- Git for version control
- Flask for local web server during development
- Github Copilot for code code and documentation assistance

**Methods:** 

- Plant UML for diagrams
- OOD principles for software design
- Test-driven development for API testing
- OOP for modular and maintainable code structure
- Design patterns
- Dependency injection for decoupling components
- Unit testing for API endpoints
- RESTful API design for web server endpoints

