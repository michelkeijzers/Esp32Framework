#pragma once
#include "IHttpServerAdapter.h"
#include <unordered_map>
#include <string>
#include <functional>

// Example test adapter that can register handlers for endpoints
class TestHttpServerAdapter : public IHttpServerAdapter {
public:
    using Handler = std::function<std::string(const std::string& body)>;
    void registerHandler(const std::string& method, const std::string& path, Handler handler) {
        handlers_[method + path] = handler;
    }
    std::string simulateRequest(const std::string& method, const std::string& path, const std::string& body = "") override {
        auto it = handlers_.find(method + path);
        if (it != handlers_.end()) {
            return it->second(body);
        }
        return "404 Not Found";
    }
private:
    std::unordered_map<std::string, Handler> handlers_;
};
