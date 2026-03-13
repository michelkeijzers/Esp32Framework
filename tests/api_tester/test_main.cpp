#include "IHttpServerAdapter.h"
#include "TestHttpServerAdapter.h"
#include <iostream>
#include <cassert>


int main() {
    // Create the test adapter
    TestHttpServerAdapter adapter;
    // Register endpoint handler
    adapter.registerHandler("PUT", "/api/save_preset/2", save_preset_handler);
    // Simulate a request
    std::string response = adapter.simulateRequest("PUT", "/api/save_preset/2", "");
    std::cout << "Response: " << response << std::endl;
    assert(response == "{\"status\":\"ok\"}");
    std::cout << "Test passed!" << std::endl;
    return 0;
}
