#pragma once

#include "common/esp/esp_http_server/IEspHttpServer.hpp"
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

/**
 * @brief Context for HttpTask
 * Contains all dependencies needed by HttpTask and its API classes
 */
class HttpTaskContext
{
  public:
    // ESP Services
    IEspHttpServer *httpServer;

    // Common APIs
    IApiStatus *apiStatus;
    IApiNodes *apiNodes;
    IApiSystem *apiSystem;
    IApiFirmware *apiFirmware;
    IApiSecurity *apiSecurity;
    IApiLogging *apiLogging;

    // Project-specific APIs
    IApiConfig *apiConfig;
    IApiPresets *apiPresets;
    IApiPresetValues *apiPresetValues;

    // Managers
    IPresetManager *presetManager;

    HttpTaskContext(IEspHttpServer *httpServer, IApiStatus *apiStatus, IApiNodes *apiNodes, IApiSystem *apiSystem,
                    IApiFirmware *apiFirmware, IApiSecurity *apiSecurity, IApiLogging *apiLogging,
                    IApiConfig *apiConfig, IApiPresets *apiPresets, IApiPresetValues *apiPresetValues,
                    IPresetManager *presetManager)
        : httpServer(httpServer), apiStatus(apiStatus), apiNodes(apiNodes), apiSystem(apiSystem),
          apiFirmware(apiFirmware), apiSecurity(apiSecurity), apiLogging(apiLogging), apiConfig(apiConfig),
          apiPresets(apiPresets), apiPresetValues(apiPresetValues), presetManager(presetManager)
    {
    }
};
