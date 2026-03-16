#pragma once

#include "Webserver.hpp"
#include "IDmxControllerWebserver.hpp"

#include "../dmx_controller/apis/ApiConfig.hpp"
#include "../dmx_controller/apis/ApiPresets.hpp"
#include "../dmx_controller/apis/ApiPresetValues.hpp"


class IEspNvs;
class IPresetManager;
class DmxControllerWebserver : public Webserver, public IDmxControllerWebserver
{
public:
    explicit DmxControllerWebserver(IEspLittleFs& espLittleFs, IEspHttpServer& espHttpServer, IEspNvs& nvsManager, IEspLogger& logger,
                                         IApiStatus& apiStatus, IApiNodes& apiNodes, IApiSystem& apiSystem,
                                         IApiFirmware& apiFirmware, IApiSecurity& apiSecurity, IApiLogging& apiLogging,
                                         IApiConfig* apiConfig, IApiPresets* apiPresets, IApiPresetValues* apiPresetValues,
                                         IPresetManager& presetManager);
    ~DmxControllerWebserver();

    void start() override;
    void stop() override;

protected:
    /**
     * Override register_endpoints to include both generic and DMX-specific endpoints
     */
    void register_endpoints() override;

private:
    IEspNvs& nvsManager_;
    IPresetManager& presetManager_;

    // DMX-specific API pointers (concrete)
    IApiConfig* apiConfig_;
    IApiPresets* apiPresets_;
    IApiPresetValues* apiPresetValues_;
    void register_dmx_endpoints();
    void register_endpoints_esp32();
    void register_endpoints_test();
};
