#pragma once
#include "MockEspHttpServer.hpp"
#include "ApiConfig.hpp"
#include <iostream>
#include <cassert>

class ApiConfigTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiConfig Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiConfig apiConfig(mockServer);
        
        if (!testGetConfig(mockServer, apiConfig)) return false;
        
        std::cout << "All ApiConfig tests passed!" << std::endl;
        return true;
    }

private:
    bool testGetConfig(MockEspHttpServer& mockServer, ApiConfig& apiConfig) {
        std::cout << "Testing get_config..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("GET", "/api/v1/config", [&apiConfig](const std::string& body) {
            httpd_req_t req{};
            apiConfig.get_config_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("GET", "/api/v1/config", "");
        assert(!response.empty());
        
        std::cout << "PASSED: get_config test passed" << std::endl;
        return true;
    }
};
