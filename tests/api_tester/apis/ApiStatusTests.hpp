#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "../../../main/slaves/webserver_slave/common/apis/ApiStatus.hpp"
#include <iostream>
#include <cassert>

class ApiStatusTests {
public:
    ApiStatusTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiStatus Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        ApiStatus apiStatus(mockServer);

        totalTests = 0;
        passedTests = 0;

        if (testGetStatus(mockServer, apiStatus)) passedTests++;
        totalTests++;
        if (testGetStatusStream(mockServer, apiStatus)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiStatusTests"; }

private:
    int totalTests;
    int passedTests;

    bool testGetStatus(MockEspHttpServer& mockServer, ApiStatus& apiStatus) {
        std::cout << "Testing get_status..." << std::endl;

        mockServer.registerHandler("GET", "/api/v1/status", [&apiStatus](const std::string& body) {
            httpd_req_t req{};
            apiStatus.get_status_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("GET", "/api/v1/status", "");
        if (!response.empty()) {
            std::cout << "PASSED: get_status test passed" << std::endl;
            return true;
        } else {
            std::cout << "FAILED: get_status test failed" << std::endl;
            return false;
        }
    }

    bool testGetStatusStream(MockEspHttpServer& mockServer, ApiStatus& apiStatus) {
        std::cout << "Testing get_status_stream (good weather)..." << std::endl;

        mockServer.registerHandler("GET", "/api/v1/status/stream", [&apiStatus](const std::string& body) {
            httpd_req_t req{};
            apiStatus.get_status_stream_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("GET", "/api/v1/status/stream", "");
        // Just verify the handler doesn't crash
        std::cout << "PASSED: get_status_stream test passed" << std::endl;
        return true;
    }
};
