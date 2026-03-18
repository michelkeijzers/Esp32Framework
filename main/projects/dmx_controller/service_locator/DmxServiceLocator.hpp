#pragma once

#include "common/esp/esp_file_systems/IEspLittleFs.hpp"
#include "common/esp/esp_file_systems/EspLittleFs.hpp"
#include "common/esp/esp_http_server/IEspHttpServer.hpp"
#include "common/esp/esp_http_server/EspHttpServer.hpp"
#include "common/esp/esp_nvs/IEspNvs.hpp"
#include "common/esp/esp_nvs/EspNvs.hpp"
#include "common/esp/esp_logger/IEspLogger.hpp"
#include "common/esp/esp_logger/EspLogger.hpp"
#include "common/nodes/webserver/http_task/apis/ApiStatus.hpp"
#include "common/nodes/webserver/http_task/apis/ApiNodes.hpp"
#include "common/nodes/webserver/http_task/apis/ApiSystem.hpp"
#include "common/nodes/webserver/http_task/apis/ApiFirmware.hpp"
#include "common/nodes/webserver/http_task/apis/ApiSecurity.hpp"
#include "common/nodes/webserver/http_task/apis/ApiLogging.hpp"
#include "projects/dmx_controller/http_task/apis/ApiConfig.hpp"
#include "projects/dmx_controller/http_task/apis/ApiPresets.hpp"
#include "projects/dmx_controller/http_task/apis/ApiPresetValues.hpp"
#include "projects/dmx_controller/presets_task/PresetManager.hpp"
#include "projects/dmx_controller/service_locator/HttpTaskContext.hpp"
#include "projects/dmx_controller/service_locator/PresetsTaskContext.hpp"
#include "projects/dmx_controller/service_locator/DmxControllerTaskContext.hpp"

/**
 * @brief Root Service Locator for DMX Controller
 * Holds all core ESP services and API instances
 * Provides methods to create task-specific contexts
 */

class DmxServiceLocator
{
  private:
    // Core ESP Services
    IEspLittleFs *littleFs_;
    IEspHttpServer *espHttpServer_;
    IEspNvs *nvs_;
    IEspLogger *logger_;

    // Common APIs
    IApiStatus *apiStatus_;
    IApiNodes *apiNodes_;
    IApiSystem *apiSystem_;
    IApiFirmware *apiFirmware_;
    IApiSecurity *apiSecurity_;
    IApiLogging *apiLogging_;

    // Project-specific
    IPresetManager *presetManager_;
    IApiConfig *apiConfig_;
    IApiPresets *apiPresets_;
    IApiPresetValues *apiPresetValues_;

    // Sub-contexts (created on demand)
    HttpTaskContext *httpTaskContext_;
    PresetsTaskContext *presetsTaskContext_;
    DmxControllerTaskContext *dmxControllerTaskContext_;

    // Internal creation helpers
    void createEspServices()
    {
        // Replace with actual implementations as needed
        littleFs_ = new EspLittleFs();
        espHttpServer_ = new EspHttpServer();
        nvs_ = new EspNvs();
        logger_ = new EspLogger();
    }

    void createCommonApis()
    {
        apiStatus_ = new ApiStatus(*espHttpServer_);
        apiNodes_ = new ApiNodes(*espHttpServer_);
        apiSystem_ = new ApiSystem(*espHttpServer_);
        apiFirmware_ = new ApiFirmware(*espHttpServer_);
        apiSecurity_ = new ApiSecurity(*espHttpServer_);
        apiLogging_ = new ApiLogging(*espHttpServer_);
    }

    void createProjectServices()
    {
        presetManager_ = new PresetManager(*nvs_);
        apiConfig_ = new ApiConfig(*espHttpServer_, *nvs_);
        apiPresets_ = new ApiPresets(*espHttpServer_, *presetManager_);
        apiPresetValues_ = new ApiPresetValues(*espHttpServer_, *presetManager_);
    }

  public:
    DmxServiceLocator()
        : littleFs_(nullptr), espHttpServer_(nullptr), nvs_(nullptr), logger_(nullptr), apiStatus_(nullptr),
          apiNodes_(nullptr), apiSystem_(nullptr), apiFirmware_(nullptr), apiSecurity_(nullptr), apiLogging_(nullptr),
          presetManager_(nullptr), apiConfig_(nullptr), apiPresets_(nullptr), apiPresetValues_(nullptr),
          httpTaskContext_(nullptr), presetsTaskContext_(nullptr), dmxControllerTaskContext_(nullptr)
    {
        createEspServices();
        createCommonApis();
        createProjectServices();
    }

    // Factory method to create HttpTaskContext
    HttpTaskContext *createHttpTaskContext()
    {
        if (!httpTaskContext_)
        {
            httpTaskContext_ =
                new HttpTaskContext(espHttpServer_, apiStatus_, apiNodes_, apiSystem_, apiFirmware_, apiSecurity_,
                                    apiLogging_, apiConfig_, apiPresets_, apiPresetValues_, presetManager_);
        }
        return httpTaskContext_;
    }

    // Factory method to create PresetsTaskContext
    PresetsTaskContext *createPresetsTaskContext()
    {
        if (!presetsTaskContext_)
        {
            presetsTaskContext_ = new PresetsTaskContext(logger_, nvs_, presetManager_);
        }
        return presetsTaskContext_;
    }

    // Factory method to create DmxControllerTaskContext
    DmxControllerTaskContext *createDmxControllerTaskContext()
    {
        if (!dmxControllerTaskContext_)
        {
            dmxControllerTaskContext_ =
                new DmxControllerTaskContext(logger_, createHttpTaskContext(), createPresetsTaskContext());
        }
        return dmxControllerTaskContext_;
    }

    // Getters for core services (optional, for direct access if needed)
    IEspLogger *getLogger() const { return logger_; }
    IEspHttpServer *getHttpServer() const { return espHttpServer_; }
    IEspNvs *getNvs() const { return nvs_; }
    IEspLittleFs *getLittleFs() const { return littleFs_; }

    // For testing: allow injection of mocks (optional)
    void setEspServices(IEspLittleFs *littleFs, IEspHttpServer *httpServer, IEspNvs *nvs, IEspLogger *logger)
    {
        this->littleFs_ = littleFs;
        this->espHttpServer_ = httpServer;
        this->nvs_ = nvs;
        this->logger_ = logger;
    }
    void setCommonApis(ApiStatus *apiStatus, ApiNodes *apiNodes, ApiSystem *apiSystem, ApiFirmware *apiFirmware,
                       ApiSecurity *apiSecurity, ApiLogging *apiLogging)
    {
        this->apiStatus_ = apiStatus;
        this->apiNodes_ = apiNodes;
        this->apiSystem_ = apiSystem;
        this->apiFirmware_ = apiFirmware;
        this->apiSecurity_ = apiSecurity;
        this->apiLogging_ = apiLogging;
    }
    void setProjectServices(PresetManager *presetManager, ApiConfig *apiConfig, ApiPresets *apiPresets,
                            ApiPresetValues *apiPresetValues)
    {
        this->presetManager_ = presetManager;
        this->apiConfig_ = apiConfig;
        this->apiPresets_ = apiPresets;
        this->apiPresetValues_ = apiPresetValues;
    }
};
