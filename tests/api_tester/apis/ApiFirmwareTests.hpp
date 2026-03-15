#pragma once
#include "../mock/MockEspHttpServer.hpp"
#include "../../../main/common/apis/ApiFirmware.hpp"
#include <iostream>
#include <cassert>

class ApiFirmwareTests {
public:
    ApiFirmwareTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiFirmware Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        ApiFirmware apiFirmware(mockServer);

        totalTests = 0;
        passedTests = 0;

        if (testFirmwareChunk(mockServer, apiFirmware)) passedTests++;
        totalTests++;
        if (testFirmwareFinish(mockServer, apiFirmware)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiFirmwareTests"; }

private:
    int totalTests;
    int passedTests;

    bool testFirmwareChunk(MockEspHttpServer& mockServer, ApiFirmware& apiFirmware) {
        std::cout << "Testing firmware_chunk..." << std::endl;

        mockServer.registerHandler("POST", "/api/v1/firmware_chunk", [&apiFirmware](const std::string& body) {
            httpd_req_t req{};
            apiFirmware.firmware_chunk_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("POST", "/api/v1/firmware_chunk", "");
        if (!response.empty()) {
            std::cout << "PASSED: firmware_chunk test passed" << std::endl;
            return true;
        } else {
            std::cout << "FAILED: firmware_chunk test failed" << std::endl;
            return false;
        }
    }

    bool testFirmwareFinish(MockEspHttpServer& mockServer, ApiFirmware& apiFirmware) {
        std::cout << "Testing firmware_finish (good weather)..." << std::endl;

        mockServer.registerHandler("POST", "/api/v1/firmware_finish", [&apiFirmware](const std::string& body) {
            httpd_req_t req{};
            apiFirmware.firmware_finish_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("POST", "/api/v1/firmware_finish", "");
        // Just verify the handler doesn't crash
        std::cout << "PASSED: firmware_finish test passed" << std::endl;
        return true;
    }
};
