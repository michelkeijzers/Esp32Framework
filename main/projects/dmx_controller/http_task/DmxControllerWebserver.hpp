#pragma once

#include "../../../common/nodes/webserver/http_task/ApiServer.hpp"
#include "IDmxControllerWebserver.hpp"
#include "../../../common/context/Contexts.hpp"

#include "apis/ApiConfig.hpp"
#include "apis/ApiPresets.hpp"
#include "apis/ApiPresetValues.hpp"

class IPresetManager;

class DmxControllerWebserver : public ApiServer, public IDmxControllerWebserver
{
  public:
    explicit DmxControllerWebserver(Contexts &contexts, IApiConfig &apiConfig, IApiPresets &apiPresets,
                                    IApiPresetValues &apiPresetValues, IPresetManager &presetManager);
    ~DmxControllerWebserver();

    void start() override;
    void stop() override;

  protected:
    /**
     * Override register_endpoints to include both generic and DMX-specific endpoints
     */
    void register_endpoints() override;

  private:
    IPresetManager &presetManager_;

    // DMX-specific API references (concrete)
    IApiConfig &apiConfig_;
    IApiPresets &apiPresets_;
    IApiPresetValues &apiPresetValues_;
    void register_dmx_endpoints();
    void register_endpoints_esp32();
    void register_endpoints_test();
};
