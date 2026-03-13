
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
#include <iostream>
#include <cassert>


int main() {
    // Create the mock HTTP server
    MockEspHttpServer mockServer;
    ApiPresets apiPresets(mockServer);
    ApiConfig apiConfig(mockServer);
    ApiStatus apiStatus(mockServer);
    ApiPresetValues apiPresetValues(mockServer);
    ApiNodes apiNodes(mockServer);
    ApiSystem apiSystem(mockServer);
    ApiFirmware apiFirmware(mockServer);
    ApiSecurity apiSecurity(mockServer);
    ApiLogging apiLogging(mockServer);

    // Register endpoint handler using the real ApiPresets handler
    mockServer.registerHandler("PUT", "/api/save_preset/2", [&apiPresets](const std::string& body) {
        httpd_req_t req;
        apiPresets.save_preset_handler(&req);
        return req.response;
    });
    // Simulate a request
    std::string response = mockServer.simulateRequest("PUT", "/api/save_preset/2", "");
    std::cout << "Response: " << response << std::endl;
    std::cout << "Expected: {\"ack\":\"ok\"}" << std::endl;
    assert(response == "{\"ack\":\"ok\"}");
    std::cout << "Test passed!" << std::endl;
    return 0;
}
