#pragma once
#include "../mocks/esp32/MockEspHttpServer.hpp"
#include "../../../main/common/nodes/webserver/common/apis/ApiLogging.hpp"
#include <iostream>
#include <cassert>

class ApiLoggingTests {
public:
    ApiLoggingTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiLogging Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        ApiLogging apiLogging(mockServer);

        totalTests = 0;
        passedTests = 0;

        if (testLogging(mockServer, apiLogging)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiLoggingTests"; }

private:
    int totalTests;
    int passedTests;

    bool testLogging(MockEspHttpServer& mockServer, ApiLogging& apiLogging) {
        std::cout << "Testing logging..." << std::endl;

        mockServer.registerHandler("GET", "/api/v1/logging", [&apiLogging](const std::string& body) {
            httpd_req_t req{};
            apiLogging.logging_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("GET", "/api/v1/logging", "");
        if (!response.empty()) {
            std::cout << "PASSED: logging test passed" << std::endl;
            return true;
        } else {
            std::cout << "FAILED: logging test failed" << std::endl;
            return false;
        }
    }
};
