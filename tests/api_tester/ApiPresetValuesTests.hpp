#pragma once
#include "MockEspHttpServer.hpp"
#include "ApiPresetValues.hpp"
#include <iostream>
#include <cassert>

class ApiPresetValuesTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiPresetValues Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiPresetValues apiPresetValues(mockServer);
        
        if (!testGetPresetValues(mockServer, apiPresetValues)) return false;
        
        std::cout << "All ApiPresetValues tests passed!" << std::endl;
        return true;
    }

private:
    bool testGetPresetValues(MockEspHttpServer& mockServer, ApiPresetValues& apiPresetValues) {
        std::cout << "Testing get_preset_values..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("GET", "/api/v1/preset_values/1", [&apiPresetValues](const std::string& body) {
            httpd_req_t req{};
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
