
#include "MockEspHttpServer.hpp"
#include "MockEspLogger.hpp"
#include "WebserverSlave.hpp"
#include "ApiPresetsTests.hpp"
#include "ApiStatusTests.hpp"
#include "ApiConfigTests.hpp"
#include "ApiFirmwareTests.hpp"
#include "ApiLoggingTests.hpp"
#include "ApiNodesTests.hpp"
#include "ApiPresetValuesTests.hpp"
#include "ApiSecurityTests.hpp"
#include "ApiSystemTests.hpp"
#include <iostream>
#include <cassert>


int main() {
    std::cout << "Starting API Tester - Running all API tests...\n" << std::endl;
    
    int testsRun = 0;
    int testsPassed = 0;
    
    // Run all test classes
    ApiPresetsTests apiPresetsTests;
    if (apiPresetsTests.run()) testsPassed++;
    testsRun++;
    
    ApiStatusTests apiStatusTests;
    if (apiStatusTests.run()) testsPassed++;
    testsRun++;
    
    ApiConfigTests apiConfigTests;
    if (apiConfigTests.run()) testsPassed++;
    testsRun++;
    
    ApiFirmwareTests apiFirmwareTests;
    if (apiFirmwareTests.run()) testsPassed++;
    testsRun++;
    
    ApiLoggingTests apiLoggingTests;
    if (apiLoggingTests.run()) testsPassed++;
    testsRun++;
    
    ApiNodesTests apiNodesTests;
    if (apiNodesTests.run()) testsPassed++;
    testsRun++;
    
    ApiPresetValuesTests apiPresetValuesTests;
    if (apiPresetValuesTests.run()) testsPassed++;
    testsRun++;
    
    ApiSecurityTests apiSecurityTests;
    if (apiSecurityTests.run()) testsPassed++;
    testsRun++;
    
    ApiSystemTests apiSystemTests;
    if (apiSystemTests.run()) testsPassed++;
    testsRun++;
    
    // Summary
    std::cout << "\n========================================" << std::endl;
    std::cout << "Test Summary: " << testsPassed << "/" << testsRun << " test suites passed" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    return (testsPassed == testsRun) ? 0 : 1;
}

