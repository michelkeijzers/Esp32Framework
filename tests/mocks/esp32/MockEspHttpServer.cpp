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

esp_err_t MockEspHttpServer::httpd_start(httpd_handle_t *handle, const httpd_config_t *config) {
	return ESP_OK;
}

esp_err_t MockEspHttpServer::httpd_stop(httpd_handle_t handle) { return ESP_OK; }

int MockEspHttpServer::httpd_req_recv(httpd_req_t *r, char *buf, size_t buf_len)
{
    return 0; // Simulate no data received
}

esp_err_t MockEspHttpServer::httpd_resp_set_type(httpd_req_t *req, const char *type) {
	return ESP_OK;
}

esp_err_t MockEspHttpServer::httpd_resp_send(httpd_req_t *req, const char *buf, size_t len) {
    response_ = buf;
	return ESP_OK;
}

esp_err_t MockEspHttpServer::httpd_resp_send_chunk(httpd_req_t *r, const char *buf, ssize_t buf_len) {
	if (buf && buf_len > 0) {
		response_ += std::string(buf, buf_len);
	}
	return ESP_OK;
}

esp_err_t MockEspHttpServer::httpd_resp_send_404(httpd_req_t *req) {
	response_ = "404 Not Found";
	return ESP_OK;
}

esp_err_t MockEspHttpServer::httpd_register_uri_handler(httpd_handle_t handle,
									 const httpd_uri_t *uri_handler) {
	std::cout << "Registering handler for URI: " << uri_handler->uri << std::endl;
	handlers_["ANY" + std::string(uri_handler->uri)] = [handler = uri_handler->handler](const std::string& body) {
		httpd_req_t req{};
		handler(&req);
		return req.response;
	};
	return ESP_OK;
}
