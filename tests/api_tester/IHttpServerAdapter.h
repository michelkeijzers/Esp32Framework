#pragma once
#include <string>
#include <functional>

// Interface for HTTP server adapter to abstract request/response handling
class IHttpServerAdapter {
public:
    virtual ~IHttpServerAdapter() = default;
    // Simulate a request to the server (for testing)
    virtual std::string simulateRequest(const std::string& method, const std::string& path, const std::string& body = "") = 0;
};
