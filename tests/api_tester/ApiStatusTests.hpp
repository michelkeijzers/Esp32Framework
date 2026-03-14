#pragma once
#include "MockEspHttpServer.hpp"
#include "ApiStatus.hpp"
#include <iostream>
#include <cassert>

class ApiStatusTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiStatus Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiStatus apiStatus(mockServer);
        
        if (!testGetStatus(mockServer, apiStatus)) return false;
        
        std::cout << "All ApiStatus tests passed!" << std::endl;
        return true;
    }

private:
    bool testGetStatus(MockEspHttpServer& mockServer, ApiStatus& apiStatus) {
        std::cout << "Testing get_status..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("GET", "/api/v1/status", [&apiStatus](const std::string& body) {
            httpd_req_t req{};
            apiStatus.get_status_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("GET", "/api/v1/status", "");
        // Response should contain status information
        assert(!response.empty());
        
        std::cout << "PASSED: get_status test passed" << std::endl;
        return true;
    }
};
