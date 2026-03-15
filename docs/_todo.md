## webserverSlave Requirements Coverage Checklist (2026-03-14)

### ✅ FINALIZED SPECIFICATIONS

#### 1. Static File Serving
- ✅ File types: **HTML, CSS, JS, PNG only**
- ✅ Max file size per file: **100 KB**
- ✅ LittleFS allocation: **512 KB total**
  - Web UI bundle: ~200 KB
  - Presets + Config: ~200 KB
  - Reserve: ~100 KB
- [ ] Implement 404 error handling for missing files
- [ ] Implement directory structure in LittleFS (e.g., `/index.html`, `/css/style.css`, `/js/app.js`)

#### 2. API Endpoints (All Required)
- [ ] `GET /api/status` - System status and health
- [ ] `GET /api/config` - Current configuration
- [ ] `POST /api/config` - Update configuration
- [ ] `GET /api/presets` - List all presets
- [ ] `POST /api/presets` - Create/update preset
- [ ] `DELETE /api/presets/{id}` - Delete preset
- [ ] `GET /api/slaves` - List connected slaves
- [ ] `POST /api/ota` - Trigger OTA update (with binary data)
- [ ] `GET /api/ota/status` - OTA progress/status
- [ ] `POST /api/wifi` - Manage Wi-Fi connection
- [ ] `POST /api/reboot` - Reboot device
- [ ] `POST /api/factory-reset` - Factory reset

#### 3. OTA (Over-the-Air) Updates
- ✅ Chunk size: **4096 bytes** (over Wi-Fi)
- ✅ Trigger method: **POST /api/ota endpoint from web UI**
- [ ] Implement chunk retry logic
- [ ] Track OTA progress (% complete)
- [ ] Implement OTA rollback on failure
- [ ] Send OTA_START and OTA_COMPLETE messages to master

#### 4. NVS (Non-Volatile Storage) - Schema
- ✅ Finalized items to store:
  - `wifi_ssid` - Wi-Fi network name
  - `wifi_password` - Wi-Fi password (max 63 chars)
  - `espnow_key` - 16-byte ESP-NOW encryption key
  - `device_name` - Device identifier
  - `preset_count` - Number of stored presets
  - `preset_{N}` - Full preset data per preset (name + 512 DMX values + enabled flag)
- [ ] Implement NVS versioning for future schema changes
- [ ] Implement factory reset (wipe all NVS except essential)

#### 5. Web UI/UX (HTMX + Pico.css)
- ✅ Configuration page (Wi-Fi, ESP-NOW key, device name)
- ✅ Presets management page (create, edit, delete, test)
- ✅ Slaves monitoring page (list, health status)
- ✅ OTA update page (upload + progress)
- ✅ System status page (network, storage, memory)
- [ ] Real-time updates via SSE (Server-Sent Events)

#### 6. Security
- ✅ Authentication: **Disabled by default** (REQ-SEC-600) - No login required
- ✅ HTTPS: **Not used** (per REQ-SEC-620) - HTTP only
- ✅ Wi-Fi: **WPA2** with support for scrambled password input
- ✅ ESP-NOW: **Static key encryption** (configurable via web UI)
- [ ] Input validation on all API endpoints
- [ ] Rate limiting on sensitive endpoints (OTA, factory reset)

#### 7. Wi-Fi & Connectivity
- ✅ Mode: **STA+AP fallback** (try router, fallback to own AP at 192.168.4.1)
- [ ] SSE messaging for real-time UI updates
- [ ] Graceful Wi-Fi loss handling (ESP-NOW continues, web UI offline)

#### 8. General Requirements Status
- ✅ All requirements from common.md reviewed
- ✅ All requirements from common_slave.md reviewed
- ✅ All requirements from webserver_slave.md reviewed
- ✅ No contradictions found
- ✅ All unclear items clarified


---

## Detailed Implementation Plan (webserverSlave)

### Phase 1: Foundation & Core Infrastructure
**Goal:** Set up the base webserver structure, NVS system, and file serving
**Status:** ✅ COMPLETE

1.1 **Partition Table Update**
   - ✅ Updated partitions.csv to 512 KB LittleFS (from 1 MB)
   - ✅ Verified builds successfully with new partition

1.2 **NVS System Setup**
   - ✅ Created NVSManager class with complete API
   - ✅ Implemented read/write/delete for string, int, and binary data
   - ✅ Implemented factory reset with schema reinitialization  
   - ✅ Added NVS versioning for future compatibility
   - ✅ Initialize defaults on first boot
   - ✅ Added to CMakeLists.txt and verified compile
   - ✅ Integrated into WebserverSlave initialization

1.3 **Static File Server (LittleFS)**
   - ✅ LittleFS mounting implemented in WebserverSlave::mount_littlefs()
   - ✅ HTTP GET handler for static files already implemented
   - ✅ 404 error handling and SPA routing (index.html fallback)
   - ✅ MIME type handling via StaticFileHandler class
   - ✅ Updated create_littlefs_image.py for 512 KB partition
   - ✅ Verified file types: HTML, CSS, JS, PNG, SVG, fonts

1.4 **Basic Web UI Structure**
   - ✅ index.html (Control Panel with navigation links)
   - ✅ public/pico.min.css (styling)
   - ✅ public/htmx.min.js (dynamic UI interactions)
   - ✅ Multiple pages: control.html, presets.html, configuration.html, nodes.html, security.html, logging.html, manual.html
   - ✅ Custom CSS (custom.css) for project-specific styling
   - ✅ Vite build configuration for bundling

**Phase 1 Summary:**
- Partition table reduced to 512 KB LittleFS with 0 build errors
- NVS (non-volatile storage) system fully functional with read/write/delete/factory-reset
- Static file server ready to serve HTML/CSS/JS from LittleFS
- Web UI structure already in place using HTMX + Pico.css framework
- All code compiles and builds successfully

### Phase 2: API Framework & Data Storage
**Goal:** Build the REST API and integrate NVS for configuration

2.1 **API Foundation**
   - ✅ Set up HTTP server routing/handlers
   - ✅ Implement JSON request/response handling
   - [ ] Implement error response format (status codes, messages)
   - [ ] Add input validation utilities

2.2 **NVS Integration for Configuration**
   - [ ] Store/retrieve Wi-Fi SSID and password
   - [ ] Store/retrieve ESP-NOW key (16 bytes)
   - [ ] Store/retrieve device name
   - [ ] Test NVS persistence across reboots

2.3 **Preset Data Management (NVS)**
   - [ ] Design preset data structure (name + 512 DMX values + enabled flag)
   - [ ] Implement preset save/load from NVS
   - [ ] Implement preset listing logic
   - [ ] Test preset count limits (512 KB LittleFS / preset size)

2.4 **API Endpoints - Configuration**
   - [ ] `GET /api/config` - Read current config
   - [ ] `POST /api/config` - Update config (wi-fi, espnow key, device name)
   - [ ] `POST /api/factory-reset` - Wipe NVS and reset

### Phase 3: Preset Management API
**Goal:** Implement preset CRUD operations

3.1 **Preset API Endpoints**
   - ✅ `GET /api/presets` - List all presets
   - ✅ `POST /api/presets` - Create new preset
   - ✅ `PUT /api/presets/{id}` - Update preset
   - ✅ `DELETE /api/presets/{id}` - Delete preset

3.2 **Preset UI Pages**
   - [ ] Preset list page with HTMX
   - [ ] Preset edit/create modal
   - [ ] DMX value input (512 sliders or text input)
   - [ ] Enable/disable toggle
   - [ ] Delete confirmation

3.3 **Preset Sync Testing**
   - ✅ Unit tests for preset endpoints pass (9/9 test suites)
   - [ ] Ensure presets persist across reboots
   - [ ] Test storage limits (how many presets fit in 512 KB?)
   - [ ] Implement warnings for storage limits

### Phase 4: System Monitoring & Status
**Goal:** Implement status endpoints and real-time updates

4.1 **Status API Endpoints**
   - [ ] `GET /api/status` - System info (uptime, memory, Wi-Fi status, storage)
   - [ ] `GET /api/slaves` - List ESP-NOW slaves (MAC, firmware version, state)

4.2 **Real-Time Updates (SSE)**
   - [ ] Implement Server-Sent Events (SSE) endpoint
   - [ ] Send periodic status updates to connected clients
   - [ ] Handle client disconnects gracefully
   - [ ] Create UI status dashboard with live updates

4.3 **Web UI Pages**
   - [ ] Status dashboard page
   - [ ] Slaves monitoring page
   - [ ] System info page

### Phase 5: OTA Update System
**Goal:** Implement firmware update mechanism

5.1 **OTA Infrastructure**
   - [ ] Implement OTA chunk receiver (4096 byte chunks)
   - [ ] Implement chunk retry/timeout logic
   - [ ] CRC validation per chunk
   - [ ] Track OTA progress

5.2 **OTA API Endpoints**
   - [ ] `POST /api/ota` - Receive OTA binary (multipart upload or chunked)
   - [ ] `GET /api/ota/status` - Get current OTA progress
   - [ ] Send OTA_START and OTA_COMPLETE messages to master

5.3 **OTA Rollback**
   - [ ] Implement boot validation
   - [ ] Implement automatic rollback on failed boot
   - [ ] Test rollback mechanism

5.4 **OTA UI**
   - [ ] OTA upload page with progress bar
   - [ ] File size validation (max 1 MB?)
   - [ ] Confirm before starting update

### Phase 6: Wi-Fi & Network Management
**Goal:** Implement Wi-Fi configuration via web UI

6.1 **Wi-Fi Configuration API**
   - [ ] `POST /api/wifi` - Update Wi-Fi SSID/password
   - [ ] `GET /api/wifi/networks` - Scan available networks
   - [ ] Auto-switch to STA mode when connected
   - [ ] Fallback to AP mode (192.168.4.1) if no route available

6.2 **Wi-Fi Settings UI**
   - [ ] Wi-Fi configuration page with network scanning
   - [ ] Password input (scrambled transmission)
   - [ ] Connection status indicator

6.3 **Resilience**
   - [ ] Graceful Wi-Fi loss (ESP-NOW continues, web UI shows offline)
   - [ ] Auto-reconnect logic

### Phase 7: Security Implementation
**Goal:** Add input validation, rate limiting, and secure handling

7.1 **Input Validation**
   - [ ] Validate all API request data (types, lengths, ranges)
   - [ ] Sanitize file paths (prevent directory traversal)
   - [ ] Limit Wi-Fi password length (max 63 chars)
   - [ ] Validate IPv4 addresses, ports, etc.

7.2 **Rate Limiting**
   - [ ] Rate limit sensitive endpoints (/api/ota, /api/factory-reset)
   - [ ] Prevent brute force or DoS attacks

7.3 **Secure Data Handling**
   - [ ] ESP-NOW key never logged or transmitted in plaintext
   - [ ] Wi-Fi password transmitted securely (scrambled or hashed)
   - [ ] Session data storage for SSE clients

### Phase 8: Testing & Verification
**Goal:** Comprehensive testing of all features

8.1 **Unit Tests**
   - [ ] NVS read/write/delete functions
   - [ ] Preset serialization/deserialization
   - [ ] File path validation
   - [ ] Input validation functions

8.2 **Integration Tests**
   - [ ] Full preset workflow (create, update, list, delete, persist)
   - [ ] Wi-Fi configuration and connection
   - [ ] OTA update simulation
   - [ ] API response formats

8.3 **System Tests**
   - [ ] Storage limits (LittleFS capacity, preset limit)
   - [ ] Wi-Fi loss and recovery
   - [ ] SSE connection lifecycle
   - [ ] Memory usage under load

8.4 **Manual Testing**
   - [ ] UI usability and responsiveness
   - [ ] All API endpoints via curl/Postman
   - [ ] OTA update with rollback simulation
   - [ ] Factory reset and recovery

### Phase 9: Documentation & Refinement
**Goal:** Document the system and gather feedback

9.1 **Code Documentation**
   - ✅ API endpoint documentation (request/response formats)
   - [ ] NVS schema documentation
   - [ ] Architecture and design decisions
   - [ ] Troubleshooting guide

9.2 **User Documentation**
   - [ ] Web UI user manual
   - [ ] Wi-Fi setup instructions
   - [ ] OTA update procedure
   - [ ] Factory reset instructions

9.3 **Final Review & Iteration**
   - [ ] Review with stakeholders
   - [ ] Address feedback
   - [ ] Optimize performance and storage

---

## Implementation Priority Order
**Based on user input: Static → API → Auth → OTA → NVS**

**Recommended execution sequence:**
1. Phase 1: Foundation (Partition, NVS, LittleFS)
2. Phase 2: API Framework & Configuration
3. Phase 3: Preset Management
4. Phase 4: Status & Monitoring
5. Phase 5: OTA System
6. Phase 6: Wi-Fi Management
7. Phase 7: Security
8. Phase 8: Testing
9. Phase 9: Documentation

---

# ✅ Progress Update (2026-03-15)

## Major Features Completed
- ✅ Robust URI parameter extraction utility (`UriParamExtractor`) implemented (no regex/exceptions, ESP-IDF safe)
- ✅ All API handlers updated to use new URI param extraction (preset/channel endpoints)
- ✅ All API handler unit tests updated and passing (including edge cases)
- ✅ Fixed test setup to ensure preset exists before value tests (no null pointer)
- ✅ All 9/9 API test suites pass (see `ApiPresetValuesTests.hpp`)
- ✅ Build is clean, no warnings/errors

## Details
- All code for URI parameter parsing is robust, exception-free, and fully tested.
- All relevant API endpoints now extract parameters using the new utility.
- All related unit/integration tests pass.

---

*Finalized: 2026-03-14*
