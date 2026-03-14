#pragma once
#include "MockEspHttpServer.hpp"
#include "ApiPresets.hpp"
#include <iostream>
#include <cassert>

class ApiPresetsTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiPresets Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiPresets apiPresets(mockServer);
        
        if (!testSavePreset(mockServer, apiPresets)) return false;
        
        std::cout << "All ApiPresets tests passed!" << std::endl;
        return true;
    }

private:
    bool testSavePreset(MockEspHttpServer& mockServer, ApiPresets& apiPresets) {
        std::cout << "Testing save_preset..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("PUT", "/api/v1/save_preset/2", [&apiPresets](const std::string& body) {
            httpd_req_t req{};
            apiPresets.save_preset_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("PUT", "/api/v1/save_preset/2", "");
        assert(response == "{\"ack\":\"ok\"}");
        
        std::cout << "PASSED: save_preset test passed" << std::endl;
        return true;
    }
};
