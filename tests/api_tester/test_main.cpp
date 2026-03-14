
#include "MockEspHttpServer.hpp"
#include "ApiPresets.hpp"
#include "ApiConfig.hpp"
#include "ApiStatus.hpp"
#include "ApiPresetValues.hpp"
#include "ApiNodes.hpp"
#include "ApiSystem.hpp"
#include "ApiFirmware.hpp"
#include "ApiSecurity.hpp"
#include "ApiLogging.hpp"
#include "WebserverSlave.hpp"
#include <iostream>
#include <cassert>


int main() {
    // Create the mock HTTP server
    MockEspHttpServer mockServer;
    
    // Create the WebserverSlave which internally creates and manages all API handlers
    WebserverSlave webserverSlave(mockServer);
    webserverSlave.start();  // Calls register_endpoints (no-op for unit tests)
    
    // For unit tests, directly use the API objects that WebserverSlave creates
    // In production, the WebserverSlave manages everything through the HTTP server
    
    // Create individual API objects to test
    ApiPresets apiPresets(mockServer);
    
    // Register endpoint handler using the real ApiPresets handler
    mockServer.registerHandler("PUT", "/api/v1/save_preset/2", [&apiPresets](const std::string& body) {
        // Create a minimal httpd_req_t for testing
        httpd_req_t req{};
        apiPresets.save_preset_handler(&req);
        return req.response;
    });
    
    // Simulate a request
    std::string response = mockServer.simulateRequest("PUT", "/api/v1/save_preset/2", "");
    std::cout << "Response: " << response << std::endl;
    std::cout << "Expected: {\"ack\":\"ok\"}" << std::endl;
    assert(response == "{\"ack\":\"ok\"}");
    std::cout << "Test passed!" << std::endl;
    return 0;
}

