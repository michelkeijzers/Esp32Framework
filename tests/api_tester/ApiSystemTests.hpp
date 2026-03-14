#pragma once
#include "MockEspHttpServer.hpp"
#include "ApiSystem.hpp"
#include <iostream>
#include <cassert>

class ApiSystemTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiSystem Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiSystem apiSystem(mockServer);
        
        if (!testReboot(mockServer, apiSystem)) return false;
        if (!testFactoryReset(mockServer, apiSystem)) return false;
        
        std::cout << "All ApiSystem tests passed!" << std::endl;
        return true;
    }

private:
    bool testReboot(MockEspHttpServer& mockServer, ApiSystem& apiSystem) {
        std::cout << "Testing reboot..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("POST", "/api/v1/reboot", [&apiSystem](const std::string& body) {
            httpd_req_t req{};
            apiSystem.reboot_handler(&req);
            return req.response;
        });
        
        // Simulate a request - reboot sends empty response which is OK
        std::string response = mockServer.simulateRequest("POST", "/api/v1/reboot", "");
        
        std::cout << "PASSED: reboot test passed" << std::endl;
        return true;
    }

    bool testFactoryReset(MockEspHttpServer& mockServer, ApiSystem& apiSystem) {
        std::cout << "Testing factory_reset..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("POST", "/api/v1/factory_reset", [&apiSystem](const std::string& body) {
            httpd_req_t req{};
            apiSystem.factory_reset_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("POST", "/api/v1/factory_reset", "");
        assert(!response.empty());
        assert(response == "{\"ack\":\"ok\"}");
        
        std::cout << "PASSED: factory_reset test passed" << std::endl;
        return true;
    }
};
