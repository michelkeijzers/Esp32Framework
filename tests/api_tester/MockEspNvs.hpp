#pragma once
#include "../../main/common/esp_nvs/IEspNvs.hpp"
#include <map>
#include <vector>

// Mock implementation of NVS for unit testing
class MockEspNvs : public IEspNvs {
public:
    MockEspNvs() = default;
    virtual ~MockEspNvs() = default;

    esp_err_t nvs_flash_init() override;

    esp_err_t nvs_open(const char *namespace_name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle) override;
    void nvs_close(nvs_handle_t handle) override;

    esp_err_t nvs_get_i32(nvs_handle_t handle, const char *key, int32_t *out_value) override;
    esp_err_t nvs_get_u32(nvs_handle_t handle, const char *key, uint32_t *out_value) override;
    esp_err_t nvs_get_i64(nvs_handle_t handle, const char *key, int64_t *out_value) override;
    esp_err_t nvs_get_u64(nvs_handle_t handle, const char *key, uint64_t *out_value) override;
    esp_err_t nvs_get_str(nvs_handle_t handle, const char *key, char *out_value, size_t *length) override;
    esp_err_t nvs_get_blob(nvs_handle_t handle, const char *key, void *out_value, size_t *length) override;

    esp_err_t nvs_set_i32(nvs_handle_t handle, const char *key, int32_t value) override;
    esp_err_t nvs_set_u32(nvs_handle_t handle, const char *key, uint32_t value) override;
    esp_err_t nvs_set_i64(nvs_handle_t handle, const char *key, int64_t value) override;
    esp_err_t nvs_set_u64(nvs_handle_t handle, const char *key, uint64_t value) override;
    esp_err_t nvs_set_str(nvs_handle_t handle, const char *key, const char *value) override;
    esp_err_t nvs_set_blob(nvs_handle_t handle, const char *key, const void *value, size_t length) override;

    esp_err_t nvs_commit(nvs_handle_t handle) override;
    esp_err_t nvs_erase_key(nvs_handle_t handle, const char *key) override;
    esp_err_t nvs_erase_all(nvs_handle_t handle) override;

    // Test helpers
    void clear() { storage_.clear(); }
    bool hasKey(const std::string &key) const { return storage_.count(key) > 0; }

private:
    struct Value {
        enum class Type { I32, U32, I64, U64, STR, BLOB } type;
        std::vector<uint8_t> data;

        Value() = default;
        Value(int32_t v) : type(Type::I32) { 
            data.resize(sizeof(v));
            *reinterpret_cast<int32_t*>(data.data()) = v;
        }
        Value(uint32_t v) : type(Type::U32) { 
            data.resize(sizeof(v));
            *reinterpret_cast<uint32_t*>(data.data()) = v;
        }
        Value(int64_t v) : type(Type::I64) { 
            data.resize(sizeof(v));
            *reinterpret_cast<int64_t*>(data.data()) = v;
        }
        Value(uint64_t v) : type(Type::U64) { 
            data.resize(sizeof(v));
            *reinterpret_cast<uint64_t*>(data.data()) = v;
        }
        Value(const std::string &v) : type(Type::STR) { 
            data.resize(v.length() + 1);
            std::memcpy(data.data(), v.c_str(), v.length() + 1);
        }
        Value(const void *v, size_t len, Type t) : type(t) { 
            data.resize(len);
            std::memcpy(data.data(), v, len);
        }
    };

    std::map<std::string, Value> storage_;
};
