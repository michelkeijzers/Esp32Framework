#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "ApiFirmware.hpp"
#include <iostream>
#include <cassert>

class ApiFirmwareTests {
public:
    bool run() {
        std::cout << "\n=== Running ApiFirmware Tests ===" << std::endl;
        
        MockEspHttpServer mockServer;
        ApiFirmware apiFirmware(mockServer);
        
        if (!testFirmwareChunk(mockServer, apiFirmware)) return false;
        
        std::cout << "All ApiFirmware tests passed!" << std::endl;
        return true;
    }

private:
    bool testFirmwareChunk(MockEspHttpServer& mockServer, ApiFirmware& apiFirmware) {
        std::cout << "Testing firmware_chunk..." << std::endl;
        
        // Register endpoint handler
        mockServer.registerHandler("POST", "/api/v1/firmware_chunk", [&apiFirmware](const std::string& body) {
            httpd_req_t req{};
            apiFirmware.firmware_chunk_handler(&req);
            return req.response;
        });
        
        // Simulate a request
        std::string response = mockServer.simulateRequest("POST", "/api/v1/firmware_chunk", "");
        assert(!response.empty());
        
        std::cout << "PASSED: firmware_chunk test passed" << std::endl;
        return true;
    }
};
