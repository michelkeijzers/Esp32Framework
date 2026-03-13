#include "IHttpServerAdapter.h"
#include "TestHttpServerAdapter.h"
#include "mock_esp_http_server.h"
#include "ApiPresets.hpp"
#include <iostream>
#include <cassert>

int main() {
    // Create the test adapter
    TestHttpServerAdapter adapter;
    // Register endpoint handler using the real ApiPresets handler
    adapter.registerHandler("PUT", "/api/save_preset/2", [](const std::string& body) {
        httpd_req_t req;
        ApiPresets::save_preset_handler(&req);
        return req.response;
    });
    // Simulate a request
    std::string response = adapter.simulateRequest("PUT", "/api/save_preset/2", "");
    std::cout << "Response: " << response << std::endl;
    assert(response == "{\"ack\":\"ok\"}");
    std::cout << "Test passed!" << std::endl;
    return 0;
}
