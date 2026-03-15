
#include "MockEspHttpServer.hpp"
#include "MockEspLogger.hpp"
#include "DmxControllerWebserverSlave.hpp"
#include "apis/ApiPresetsTests.hpp"
#include "apis/ApiStatusTests.hpp"
#include "apis/ApiConfigTests.hpp"
#include "apis/ApiFirmwareTests.hpp"
#include "apis/ApiLoggingTests.hpp"
#include "apis/ApiNodesTests.hpp"
#include "apis/ApiPresetValuesTests.hpp"
#include "apis/ApiSecurityTests.hpp"
#include "apis/ApiSystemTests.hpp"
#include <iostream>
#include <cassert>


int main() {
    std::cout << "Starting API Tester - Running all API tests...\n" << std::endl;
    
    int totalTestCases = 0;
    int totalPassedCases = 0;
    bool anyFailed = false;

    struct TestResult {
        const char* fileName;
        int passed;
        int total;
    };
    std::vector<TestResult> results;

    ApiPresetsTests apiPresetsTests;
    apiPresetsTests.run();
    results.push_back({apiPresetsTests.getTestFileName(), apiPresetsTests.getPassedTests(), apiPresetsTests.getTotalTests()});

    ApiStatusTests apiStatusTests;
    apiStatusTests.run();
    results.push_back({apiStatusTests.getTestFileName(), apiStatusTests.getPassedTests(), apiStatusTests.getTotalTests()});

    ApiConfigTests apiConfigTests;
    apiConfigTests.run();
    results.push_back({apiConfigTests.getTestFileName(), apiConfigTests.getPassedTests(), apiConfigTests.getTotalTests()});

    ApiFirmwareTests apiFirmwareTests;
    apiFirmwareTests.run();
    results.push_back({apiFirmwareTests.getTestFileName(), apiFirmwareTests.getPassedTests(), apiFirmwareTests.getTotalTests()});

    ApiLoggingTests apiLoggingTests;
    apiLoggingTests.run();
    results.push_back({apiLoggingTests.getTestFileName(), apiLoggingTests.getPassedTests(), apiLoggingTests.getTotalTests()});

    ApiNodesTests apiNodesTests;
    apiNodesTests.run();
    results.push_back({apiNodesTests.getTestFileName(), apiNodesTests.getPassedTests(), apiNodesTests.getTotalTests()});

    ApiPresetValuesTests apiPresetValuesTests;
    apiPresetValuesTests.run();
    results.push_back({apiPresetValuesTests.getTestFileName(), apiPresetValuesTests.getPassedTests(), apiPresetValuesTests.getTotalTests()});

    ApiSecurityTests apiSecurityTests;
    apiSecurityTests.run();
    results.push_back({apiSecurityTests.getTestFileName(), apiSecurityTests.getPassedTests(), apiSecurityTests.getTotalTests()});

    ApiSystemTests apiSystemTests;
    apiSystemTests.run();
    results.push_back({apiSystemTests.getTestFileName(), apiSystemTests.getPassedTests(), apiSystemTests.getTotalTests()});

    // Print summary per file
    std::cout << "\n========================================" << std::endl;
    for (const auto& r : results) {
        totalTestCases += r.total;
        totalPassedCases += r.passed;
        if (r.passed != r.total) anyFailed = true;
        if (r.passed == r.total) {
            std::cout << "File " << r.fileName << ": passed: " << r.passed << " / " << r.total << " tests" << std::endl;
        } else {
            std::cout << "\033[31mFile " << r.fileName << ": passed: " << r.passed << " / " << r.total << " tests\033[0m" << std::endl;
        }
    }
    std::cout << "----------------------------------------" << std::endl;
    if (!anyFailed) {
        std::cout << "Total: passed: " << totalPassedCases << "/" << totalTestCases << " tests" << std::endl;
    } else {
        std::cout << "\033[31mTotal: passed: " << totalPassedCases << "/" << totalTestCases << " tests\033[0m" << std::endl;
    }
    std::cout << "========================================\n" << std::endl;

    return anyFailed ? 1 : 0;
}

