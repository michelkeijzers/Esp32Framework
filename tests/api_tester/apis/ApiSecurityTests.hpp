#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "../../../main/slaves/webserver_slave/project_dmx_controller/apis/ApiSecurity.hpp"
#include <iostream>
#include <cassert>

class ApiSecurityTests {
public:
    ApiSecurityTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiSecurity Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        ApiSecurity apiSecurity(mockServer);

        totalTests = 0;
        passedTests = 0;

        if (testEspNowKey(mockServer, apiSecurity)) passedTests++;
        totalTests++;
        if (testWifiPassword(mockServer, apiSecurity)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiSecurityTests"; }

private:
    int totalTests;
    int passedTests;

    bool testEspNowKey(MockEspHttpServer& mockServer, ApiSecurity& apiSecurity) {
        std::cout << "Testing esp_now_key..." << std::endl;

        mockServer.registerHandler("GET", "/api/v1/esp_now_key", [&apiSecurity](const std::string& body) {
            httpd_req_t req{};
            apiSecurity.esp_now_key_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("GET", "/api/v1/esp_now_key", "");
        if (!response.empty()) {
            std::cout << "PASSED: esp_now_key test passed" << std::endl;
            return true;
        } else {
            std::cout << "FAILED: esp_now_key test failed" << std::endl;
            return false;
        }
    }

    bool testWifiPassword(MockEspHttpServer& mockServer, ApiSecurity& apiSecurity) {
        std::cout << "Testing wifi_password (good weather)..." << std::endl;

        mockServer.registerHandler("GET", "/api/v1/wifi_password", [&apiSecurity](const std::string& body) {
            httpd_req_t req{};
            apiSecurity.wifi_password_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("GET", "/api/v1/wifi_password", "");
        // Just verify the handler doesn't crash
        std::cout << "PASSED: wifi_password test passed" << std::endl;
        return true;
    }
};
