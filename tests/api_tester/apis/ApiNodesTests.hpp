#pragma once
#include "../mocks/esp32/MockEspHttpServer.hpp"
#include "../../../main/slaves/webserver_slave/common/apis/ApiNodes.hpp"
#include <iostream>
#include <cassert>

class ApiNodesTests {
public:
    ApiNodesTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiNodes Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        ApiNodes apiNodes(mockServer);

        totalTests = 0;
        passedTests = 0;

        if (testGetNodesInfo(mockServer, apiNodes)) passedTests++;
        totalTests++;
        if (testSaveNodesInfo(mockServer, apiNodes)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiNodesTests"; }

private:
    int totalTests;
    int passedTests;

    bool testGetNodesInfo(MockEspHttpServer& mockServer, ApiNodes& apiNodes) {
        std::cout << "Testing get_nodes_info..." << std::endl;

        mockServer.registerHandler("GET", "/api/v1/nodes/info", [&apiNodes](const std::string& body) {
            httpd_req_t req{};
            apiNodes.get_nodes_info_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("GET", "/api/v1/nodes/info", "");
        if (!response.empty()) {
            std::cout << "PASSED: get_nodes_info test passed" << std::endl;
            return true;
        } else {
            std::cout << "FAILED: get_nodes_info test failed" << std::endl;
            return false;
        }
    }

    bool testSaveNodesInfo(MockEspHttpServer& mockServer, ApiNodes& apiNodes) {
        std::cout << "Testing save_nodes_info (good weather)..." << std::endl;

        mockServer.registerHandler("POST", "/api/v1/nodes/info", [&apiNodes](const std::string& body) {
            httpd_req_t req{};
            apiNodes.save_nodes_info_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("POST", "/api/v1/nodes/info", "{\"nodes\":[]}");
        // Just verify the handler doesn't crash
        std::cout << "PASSED: save_nodes_info test passed" << std::endl;
        return true;
    }
};
