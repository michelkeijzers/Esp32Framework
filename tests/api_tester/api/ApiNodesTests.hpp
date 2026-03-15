#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "ApiNodes.hpp"
#include <iostream>
#include <cassert>

class ApiNodesTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiNodes Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiNodes apiNodes(mockServer);
        
        if (!testGetNodesInfo(mockServer, apiNodes)) return false;
        
        std::cout << "All ApiNodes tests passed!" << std::endl;
        return true;
    }

private:
    bool testGetNodesInfo(MockEspHttpServer& mockServer, ApiNodes& apiNodes) {
        std::cout << "Testing get_nodes_info..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("GET", "/api/v1/nodes/info", [&apiNodes](const std::string& body) {
            httpd_req_t req{};
            apiNodes.get_nodes_info_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("GET", "/api/v1/nodes/info", "");
        assert(!response.empty());
        
        std::cout << "PASSED: get_nodes_info test passed" << std::endl;
        return true;
    }
};
