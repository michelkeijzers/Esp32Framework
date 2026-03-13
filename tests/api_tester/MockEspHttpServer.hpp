#pragma once
#include "IEspHttpServer.hpp"
#include <unordered_map>
#include <string>
#include <functional>

// Mock implementation for API testing
class MockEspHttpServer : public IEspHttpServer {
public:
    void registerHandler(const std::string& method, const std::string& path, std::function<std::string(const std::string& body)> handler);
    std::string simulateRequest(const std::string& method, const std::string& path, const std::string& body = "");

    esp_err_t httpd_resp_set_type(httpd_req_t *req, const char *type) override;
    esp_err_t httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) override;

private:
    std::unordered_map<std::string, std::function<std::string(const std::string&)>> handlers_;

    std::string response_;
};
