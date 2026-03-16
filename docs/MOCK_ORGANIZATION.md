# Mock Organization Summary

## Overview
All mocks have been reorganized into a clear, hierarchical structure that separates shared mocks from test-specific mocks.

## Structure

### Root Level: `mocks/`
**Purpose:** Shared mocks used across multiple components and test suites

- **`mocks/common/`** - Shared component mocks for common webserver slave functionality
  - `MockWebserverSlave.hpp` - Mock for IWebserverSlave interface
  - `MockDmxControllerWebserverSlave.hpp` - Mock for IDmxControllerWebserverSlave interface
  - **Usage:** Included in `main/main.cpp` for flexible dependency injection across the application

### API Tester: `tests/api_tester/mocks/`
**Purpose:** All mocks specific to the API tester, organized by layer

- **`infrastructure/`** - Low-level infrastructure mocks (NOT related to business logic)
  - `MockEspHttpServer.cpp/hpp` - Mock for HTTP server functionality
  - `MockEspLogger.cpp/hpp` - Mock for logging capability
  - `MockEspNvs.cpp/hpp` - Mock for NVS (Non-Volatile Storage) operations
  - `MockEspNow.cpp/hpp` - Mock for ESP-NOW wireless communication

- **`apis/`** - API endpoint mocks (common API implementations)
  - `MockApiSystem.hpp` - Mock for system API
  - `MockApiStatus.hpp` - Mock for status API
  - `MockApiLogging.hpp` - Mock for logging API
  - `MockApiNodes.hpp` - Mock for nodes API
  - `MockApiFirmware.hpp` - Mock for firmware API
  - `MockApiSecurity.hpp` - Mock for security API

- **`dmx_controller_apis/`** - DMX controller-specific API mocks
  - `MockApiConfig.hpp` - Mock for DMX config API
  - `MockApiPresets.hpp` - Mock for presets API
  - `MockApiPresetValues.hpp` - Mock for preset values API

- **`app/`** - Application-specific mocks
  - `MockPresetManager.hpp` - Mock for preset management

## Design Principles

1. **Shared vs. Test-Specific:** Common mocks that could be used by multiple test suites are in `mocks/common/`. Test-specific mocks are in `tests/api_tester/mocks/`.

2. **Layered Organization:** Mocks within the API tester are organized by layer:
   - **Infrastructure:** Low-level system mocks (logging, storage, communication)
   - **APIs:** API endpoint implementations
   - **DMX-specific:** DMX controller API mocks
   - **App:** Application domain mocks

3. **Include Paths:** Always use relative paths from the including file's location:
   - Main code includes from root: `#include "../../mocks/common/MockXxx.hpp"`
   - API tester code includes from test dir: `#include "../mocks/infrastructure/MockXxx.hpp"`

4. **Future Expansion:** This structure easily accommodates:
   - New test suites (add `tests/new_tester/mocks/`)
   - New mock domains (add folders as needed)
   - Shared mocks across multiple testers (keep in `mocks/common/`)

## Files Modified
- `main/main.cpp` - Updated include to new mock location
- `tests/api_tester/test_main.cpp` - Updated includes
- `tests/api_tester/CMakeLists.txt` - Updated source file paths
- All test header files in `tests/api_tester/apis/` - Updated mock includes

## Old Locations Cleaned Up
- Removed `tests/mock/` directory (moved to `tests/api_tester/mocks/`)
- Removed `tests/MockXxx.hpp` files (moved to `mocks/common/`)
- Removed old mock from `main/slaves/webserver_slave/dmx_controller/`

## Build Status
✅ API tester builds successfully with new structure
✅ All includes resolve correctly
✅ No compilation errors
