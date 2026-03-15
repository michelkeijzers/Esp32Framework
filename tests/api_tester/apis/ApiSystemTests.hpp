#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "../../../main/slaves/webserver_slave/project_dmx_controller/apis/ApiSystem.hpp"
#include <iostream>
#include <cassert>

class ApiSystemTests {
public:
    ApiSystemTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiSystem Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        ApiSystem apiSystem(mockServer);

        totalTests = 0;
        passedTests = 0;

        if (testReboot(mockServer, apiSystem)) passedTests++;
        totalTests++;
        if (testFactoryReset(mockServer, apiSystem)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiSystemTests"; }

private:
    int totalTests;
    int passedTests;

    bool testReboot(MockEspHttpServer& mockServer, ApiSystem& apiSystem) {
        std::cout << "Testing reboot..." << std::endl;

        mockServer.registerHandler("POST", "/api/v1/reboot", [&apiSystem](const std::string& body) {
            httpd_req_t req{};
            apiSystem.reboot_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("POST", "/api/v1/reboot", "");
        // reboot sends empty response which is OK
        std::cout << (response.empty() ? "PASSED: reboot test passed" : "FAILED: reboot test failed") << std::endl;
        return response.empty();
    }

    bool testFactoryReset(MockEspHttpServer& mockServer, ApiSystem& apiSystem) {
        std::cout << "Testing factory_reset..." << std::endl;

        mockServer.registerHandler("POST", "/api/v1/factory_reset", [&apiSystem](const std::string& body) {
            httpd_req_t req{};
            apiSystem.factory_reset_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("POST", "/api/v1/factory_reset", "");
        if (!response.empty() && response == "{\"ack\":\"ok\"}") {
            std::cout << "PASSED: factory_reset test passed" << std::endl;
            return true;
        } else {
            std::cout << "FAILED: factory_reset test failed" << std::endl;
            return false;
        }
    }
};
