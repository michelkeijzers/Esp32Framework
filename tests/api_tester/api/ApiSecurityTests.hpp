#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "ApiSecurity.hpp"
#include <iostream>
#include <cassert>

class ApiSecurityTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiSecurity Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiSecurity apiSecurity(mockServer);
        
        if (!testEspNowKey(mockServer, apiSecurity)) return false;
        
        std::cout << "All ApiSecurity tests passed!" << std::endl;
        return true;
    }

private:
    bool testEspNowKey(MockEspHttpServer& mockServer, ApiSecurity& apiSecurity) {
        std::cout << "Testing esp_now_key..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("GET", "/api/v1/esp_now_key", [&apiSecurity](const std::string& body) {
            httpd_req_t req{};
            apiSecurity.esp_now_key_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("GET", "/api/v1/esp_now_key", "");
        assert(!response.empty());
        
        std::cout << "PASSED: esp_now_key test passed" << std::endl;
        return true;
    }
};
