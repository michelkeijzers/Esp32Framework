#include "MockEspNvs.hpp"
#include <cstring>
#include <algorithm>
#include "../../../../common/esp/esp_error/esp_error_if.hpp"

esp_err_t MockEspNvs::nvs_flash_init() {
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_open(const char *namespace_name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle) {
    if (!out_handle) return ESP_ERR_INVALID_ARG;
    *out_handle = 0;  // Mock always returns a valid handle
    return ESP_OK;
}

void MockEspNvs::nvs_close(nvs_handle_t handle) {
    // No-op for mock
}

esp_err_t MockEspNvs::nvs_get_i32(nvs_handle_t handle, const char *key, int32_t *out_value) {
    if (!key || !out_value) return ESP_ERR_INVALID_ARG;
    if (storage_.find(key) == storage_.end()) return ESP_ERR_NVS_NOT_FOUND;
    
    const auto &val = storage_[key];
    if (val.type != Value::Type::I32) return ESP_ERR_NVS_TYPE_MISMATCH;
    *out_value = *reinterpret_cast<const int32_t*>(val.data.data());
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_get_u32(nvs_handle_t handle, const char *key, uint32_t *out_value) {
    if (!key || !out_value) return ESP_ERR_INVALID_ARG;
    if (storage_.find(key) == storage_.end()) return ESP_ERR_NVS_NOT_FOUND;
    
    const auto &val = storage_[key];
    if (val.type != Value::Type::U32) return ESP_ERR_NVS_TYPE_MISMATCH;
    *out_value = *reinterpret_cast<const uint32_t*>(val.data.data());
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_get_i64(nvs_handle_t handle, const char *key, int64_t *out_value) {
    if (!key || !out_value) return ESP_ERR_INVALID_ARG;
    if (storage_.find(key) == storage_.end()) return ESP_ERR_NVS_NOT_FOUND;
    
    const auto &val = storage_[key];
    if (val.type != Value::Type::I64) return ESP_ERR_NVS_TYPE_MISMATCH;
    *out_value = *reinterpret_cast<const int64_t*>(val.data.data());
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_get_u64(nvs_handle_t handle, const char *key, uint64_t *out_value) {
    if (!key || !out_value) return ESP_ERR_INVALID_ARG;
    if (storage_.find(key) == storage_.end()) return ESP_ERR_NVS_NOT_FOUND;
    
    const auto &val = storage_[key];
    if (val.type != Value::Type::U64) return ESP_ERR_NVS_TYPE_MISMATCH;
    *out_value = *reinterpret_cast<const uint64_t*>(val.data.data());
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_get_str(nvs_handle_t handle, const char *key, char *out_value, size_t *length) {
    if (!key || !length) return ESP_ERR_INVALID_ARG;
    if (storage_.find(key) == storage_.end()) return ESP_ERR_NVS_NOT_FOUND;
    
    const auto &val = storage_[key];
    if (val.type != Value::Type::STR) return ESP_ERR_NVS_TYPE_MISMATCH;
    
    size_t len = val.data.size();
    if (out_value) {
        if (*length < len) return ESP_ERR_NVS_INVALID_LENGTH;
        std::memcpy(out_value, val.data.data(), len);
    }
    *length = len;
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_get_blob(nvs_handle_t handle, const char *key, void *out_value, size_t *length) {
    if (!key || !length) return ESP_ERR_INVALID_ARG;
    if (storage_.find(key) == storage_.end()) return ESP_ERR_NVS_NOT_FOUND;
    
    const auto &val = storage_[key];
    if (val.type != Value::Type::BLOB) return ESP_ERR_NVS_TYPE_MISMATCH;
    
    size_t len = val.data.size();
    if (out_value) {
        if (*length < len) return ESP_ERR_NVS_INVALID_LENGTH;
        std::memcpy(out_value, val.data.data(), len);
    }
    *length = len;
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_set_i32(nvs_handle_t handle, const char *key, int32_t value) {
    if (!key) return ESP_ERR_INVALID_ARG;
    storage_[key] = Value(value);
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_set_u32(nvs_handle_t handle, const char *key, uint32_t value) {
    if (!key) return ESP_ERR_INVALID_ARG;
    storage_[key] = Value(value);
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_set_i64(nvs_handle_t handle, const char *key, int64_t value) {
    if (!key) return ESP_ERR_INVALID_ARG;
    storage_[key] = Value(value);
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_set_u64(nvs_handle_t handle, const char *key, uint64_t value) {
    if (!key) return ESP_ERR_INVALID_ARG;
    storage_[key] = Value(value);
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_set_str(nvs_handle_t handle, const char *key, const char *value) {
    if (!key || !value) return ESP_ERR_INVALID_ARG;
    storage_[key] = Value(std::string(value));
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_set_blob(nvs_handle_t handle, const char *key, const void *value, size_t length) {
    if (!key || !value) return ESP_ERR_INVALID_ARG;
    storage_[key] = Value(value, length, Value::Type::BLOB);
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_commit(nvs_handle_t handle) {
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_erase_key(nvs_handle_t handle, const char *key) {
    if (!key) return ESP_ERR_INVALID_ARG;
    auto it = storage_.find(key);
    if (it == storage_.end()) return ESP_ERR_NVS_NOT_FOUND;
    storage_.erase(it);
    return ESP_OK;
}

esp_err_t MockEspNvs::nvs_erase_all(nvs_handle_t handle) {
    storage_.clear();
    return ESP_OK;
}
