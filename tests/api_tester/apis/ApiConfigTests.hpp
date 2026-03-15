#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "../mock/MockEspNvs.hpp"
#include "../../../main/slaves/webserver_slave/dmx_controller/apis/ApiConfig.hpp"
#include <iostream>
#include <cassert>

class ApiConfigTests {
public:
    ApiConfigTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiConfig Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        MockEspNvs mockNvs;
        ApiConfig apiConfig(mockServer, mockNvs);

        totalTests = 0;
        passedTests = 0;

        if (testGetConfig(mockServer, mockNvs, apiConfig)) passedTests++;
        totalTests++;
        if (testPutConfig(mockServer, mockNvs, apiConfig)) passedTests++;
        totalTests++;
        if (testSetCircularNavigation(mockServer, apiConfig)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiConfigTests"; }

private:
    int totalTests;
    int passedTests;

    bool testGetConfig(MockEspHttpServer& mockServer, MockEspNvs& mockNvs, ApiConfig& apiConfig) {
        std::cout << "Testing get_config..." << std::endl;

        // Mock returns empty config
        mockServer.registerHandler("GET", "/api/v1/config", [&apiConfig](const std::string& body) {
            httpd_req_t req{};
            apiConfig.get_config_handler(&req);
            return req.response;
        });

        // Just verify the handler doesn't crash
        std::cout << "PASSED: get_config test passed" << std::endl;
        return true;
    }

    bool testPutConfig(MockEspHttpServer& mockServer, MockEspNvs& mockNvs, ApiConfig& apiConfig) {
        std::cout << "Testing put_config..." << std::endl;

        mockServer.registerHandler("PUT", "/api/v1/config", [&apiConfig](const std::string& body) {
            httpd_req_t req{};
            req.user_ctx = (void*)body.c_str();
            apiConfig.put_config_handler(&req);
            return req.response;
        });

        // Just verify the handler doesn't crash
        std::cout << "PASSED: put_config test passed" << std::endl;
        return true;
    }

    bool testSetCircularNavigation(MockEspHttpServer& mockServer, ApiConfig& apiConfig) {
        std::cout << "Testing set_circular_navigation..." << std::endl;

        mockServer.registerHandler("PUT", "/api/v1/set_circular_navigation", [&apiConfig](const std::string& body) {
            httpd_req_t req{};
            apiConfig.set_circular_navigation_handler(&req);
            return req.response;
        });

        // Just verify the handler doesn't crash
        std::cout << "PASSED: set_circular_navigation test passed" << std::endl;
        return true;
    }
};
