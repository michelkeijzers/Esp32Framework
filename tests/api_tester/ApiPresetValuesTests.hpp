#pragma once
#include "MockEspHttpServer.hpp"
#include "MockPresetManager.hpp"
#include "ApiPresetValues.hpp"
#include <iostream>
#include <cassert>

class ApiPresetValuesTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiPresetValues Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        MockPresetManager mockPresetManager;
        ApiPresetValues apiPresetValues(mockServer, mockPresetManager);
        
        if (!testGetPresetValues(mockServer, apiPresetValues, mockPresetManager)) return false;
        
        std::cout << "All ApiPresetValues tests passed!" << std::endl;
        return true;
    }

private:
    bool testGetPresetValues(MockEspHttpServer& mockServer, ApiPresetValues& apiPresetValues, MockPresetManager& mockPresetManager) {
        std::cout << "Testing get_preset_values..." << std::endl;
        
        // Add a test preset to the mock manager
        Preset testPreset;
        testPreset.number = 1;
        testPreset.name = "Test Preset";
        testPreset.active = true;
        testPreset.universe = 1;
        for (int i = 0; i < 512; ++i) {
            testPreset.dmx_values[i] = i % 256;  // Sample values
        }
        mockPresetManager.save_preset(testPreset);
        
        // Register endpoint handler
        mockServer.registerHandler("GET", "/api/v1/preset_values/1", [&apiPresetValues](const std::string& body) {
            httpd_req_t req{};
            req.uri = "/api/v1/preset_values/1";
            apiPresetValues.get_preset_values_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("GET", "/api/v1/preset_values/1", "");
        assert(!response.empty());
        
        std::cout << "OK get_preset_values test passed" << std::endl;
        return true;
    }
};
