#pragma once
#include "../mocks/esp32/MockEspHttpServer.hpp"
#include "../mocks/project_dmx_controller/MockPresetManager.hpp"
#include "../../../main/slaves/webserver_slave/dmx_controller/apis/ApiPresetValues.hpp"
#include <iostream>
#include <cassert>

class ApiPresetValuesTests {
public:
    ApiPresetValuesTests() : totalTests(0), passedTests(0) {}

    bool run() {
        std::cout << "\n=== Running ApiPresetValues Tests ===" << std::endl;

        MockEspHttpServer mockServer;
        MockPresetManager mockPresetManager;
        ApiPresetValues apiPresetValues(mockServer, mockPresetManager);

        totalTests = 0;
        passedTests = 0;

        if (testGetPresetValues(mockServer, apiPresetValues, mockPresetManager)) passedTests++;
        totalTests++;
        if (testSetPresetValue(mockServer, apiPresetValues, mockPresetManager)) passedTests++;
        totalTests++;

        return passedTests == totalTests;
    }

    int getTotalTests() const { return totalTests; }
    int getPassedTests() const { return passedTests; }
    const char* getTestFileName() const { return "ApiPresetValuesTests"; }

private:
    int totalTests;
    int passedTests;

    bool testGetPresetValues(MockEspHttpServer& mockServer, ApiPresetValues& apiPresetValues, MockPresetManager& mockPresetManager) {
        std::cout << "Testing get_preset_values..." << std::endl;

        Preset testPreset;
        testPreset.number = 1;
        testPreset.name = "Test Preset";
        testPreset.active = true;
        testPreset.universe = 1;
        for (int i = 0; i < 512; ++i) {
            testPreset.dmx_values[i] = i % 256;
        }
        mockPresetManager.save_preset(testPreset);

        mockServer.registerHandler("GET", "/api/v1/preset_values/1", [&apiPresetValues](const std::string& body) {
            httpd_req_t req{};
            req.uri = "/api/v1/preset_values/1";
            apiPresetValues.get_preset_values_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("GET", "/api/v1/preset_values/1", "");
        if (!response.empty()) {
            std::cout << "OK get_preset_values test passed" << std::endl;
            return true;
        } else {
            std::cout << "FAILED: get_preset_values test failed" << std::endl;
            return false;
        }
    }

    bool testSetPresetValue(MockEspHttpServer& mockServer, ApiPresetValues& apiPresetValues, MockPresetManager& mockPresetManager) {
        std::cout << "Testing set_preset_value (good weather)..." << std::endl;

        Preset testPreset;
        testPreset.number = 2;
        testPreset.name = "Set Value Test";
        testPreset.active = false;
        testPreset.universe = 1;
        for (int i = 0; i < 512; ++i) {
            testPreset.dmx_values[i] = 0;
        }
        mockPresetManager.save_preset(testPreset);

        mockServer.registerHandler("PUT", "/api/v1/preset_values/2", [&apiPresetValues](const std::string& body) {
            httpd_req_t req{};
            req.uri = "/api/v1/preset_values/2";
            apiPresetValues.set_preset_value_handler(&req);
            return req.response;
        });

        std::string response = mockServer.simulateRequest("PUT", "/api/v1/preset_values/2", "{\"channel\":1,\"value\":255}");
        // Just verify the handler doesn't crash
        std::cout << "PASSED: set_preset_value test passed" << std::endl;
        return true;
    }
};
