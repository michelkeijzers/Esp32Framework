#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "ApiLogging.hpp"
#include <iostream>
#include <cassert>

class ApiLoggingTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiLogging Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiLogging apiLogging(mockServer);
        
        if (!testLogging(mockServer, apiLogging)) return false;
        
        std::cout << "All ApiLogging tests passed!" << std::endl;
        return true;
    }

private:
    bool testLogging(MockEspHttpServer& mockServer, ApiLogging& apiLogging) {
        std::cout << "Testing logging..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("GET", "/api/v1/logging", [&apiLogging](const std::string& body) {
            httpd_req_t req{};
            apiLogging.logging_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("GET", "/api/v1/logging", "");
        assert(!response.empty());
        
        std::cout << "PASSED: logging test passed" << std::endl;
        return true;
    }
};
