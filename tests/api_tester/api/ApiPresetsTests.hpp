#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "../mock/MockPresetManager.hpp"
#include "ApiPresets.hpp"
#include <iostream>
#include <cassert>

class ApiPresetsTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiPresets Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        MockPresetManager mockPresetManager;
        ApiPresets apiPresets(mockServer, mockPresetManager);
        
        if (!testGetPresets(mockServer, apiPresets)) return false;
        if (!testSavePreset(mockServer, apiPresets, mockPresetManager)) return false;
        
        std::cout << "All ApiPresets tests passed!" << std::endl;
        return true;
    }

private:
    bool testGetPresets(MockEspHttpServer& mockServer, ApiPresets& apiPresets) {
        std::cout << "Testing get_presets..." << std::endl;
        
        // Simulate a request
        mockServer.registerHandler("GET", "/api/v1/presets", [&apiPresets](const std::string& body) {
            httpd_req_t req{};
            apiPresets.get_presets_handler(&req);
            return req.response;
        });
        
        std::string response = mockServer.simulateRequest("GET", "/api/v1/presets", "");
        assert(response == "[]");  // Should be empty array if no presets
        
        std::cout << "PASSED: get_presets test passed" << std::endl;
        return true;
    }

    bool testSavePreset(MockEspHttpServer& mockServer, ApiPresets& apiPresets, MockPresetManager& mockPresetManager) {
        std::cout << "Testing save_preset..." << std::endl;
        
        // Create a preset in the manager first
        Preset testPreset(0, "Test Preset", false);
        mockPresetManager.save_preset(testPreset);
        
        // Register endpoint handler
        mockServer.registerHandler("PUT", "/api/v1/save_preset/0", [&apiPresets](const std::string& body) {
            httpd_req_t req{};
            apiPresets.save_preset_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("PUT", "/api/v1/save_preset/0", "");
        assert(response == "{\"ack\":\"ok\"}");
        
        std::cout << "PASSED: save_preset test passed" << std::endl;
        return true;
    }
};
