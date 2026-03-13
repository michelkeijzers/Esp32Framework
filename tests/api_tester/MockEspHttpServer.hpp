#pragma once
#include "IEspHttpServer.hpp"
#include <unordered_map>
#include <string>
#include <functional>

// Mock implementation for API testing
class MockEspHttpServer : public IEspHttpServer {
public:
    // These are not part of the interface, but useful for testing
    void registerHandler(const std::string& method, const std::string& path, std::function<std::string(const std::string& body)> handler) {
        handlers_[method + path] = handler;
    }
    std::string simulateRequest(const std::string& method, const std::string& path, const std::string& body = "") {
        auto it = handlers_.find(method + path);
        if (it != handlers_.end()) {
            return it->second(body);
        }
        return "404 Not Found";
    }

    // Implement the required interface methods as stubs for test
    esp_err_t httpd_resp_set_type(httpd_req_t *req, const char *type) override { return 0; }
    esp_err_t httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) override { return 0; }

private:
    std::unordered_map<std::string, std::function<std::string(const std::string&)>> handlers_;
};
