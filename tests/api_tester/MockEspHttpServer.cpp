#include "MockEspHttpServer.hpp"
#include <iostream>

void MockEspHttpServer::registerHandler(const std::string& method, const std::string& path, std::function<std::string(const std::string& body)> handler) {
	handlers_[method + path] = handler;
}

std::string MockEspHttpServer::simulateRequest(const std::string& method, const std::string& path, const std::string& body) {
	auto it = handlers_.find(method + path);
    std::cout << "Simulating request: " << method << " " << path << std::endl;
	if (it != handlers_.end()) 
    {
        it->second(body);
		return response_;
	}
	return "404 Not Found";
}

esp_err_t MockEspHttpServer::httpd_resp_set_type(httpd_req_t *req, const char *type) {
	return ESP_OK;
}

esp_err_t MockEspHttpServer::httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) {
    response_ = buf;
	return ESP_OK;
}
