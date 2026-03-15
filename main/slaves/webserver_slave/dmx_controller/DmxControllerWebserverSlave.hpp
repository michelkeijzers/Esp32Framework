#pragma once

#include "../common/WebserverSlave.hpp"

class IEspNvs;
class IPresetManager;
class ApiConfig;
class ApiPresets;
class ApiPresetValues;

/**
 * DMX Controller specific WebserverSlave implementation
 * Extends the base class to add DMX controller features and project-specific APIs
 */
class DmxControllerWebserverSlave : public WebserverSlave
{
public:
    explicit DmxControllerWebserverSlave(IEspLittleFs& espLittleFs, IEspHttpServer& espHttpServer, IEspNvs& nvsManager, IEspLogger& logger);
    ~DmxControllerWebserverSlave();

    void start() override;

protected:
    /**
     * Override register_endpoints to include both generic and DMX-specific endpoints
     */
    void register_endpoints() override;

private:
    IEspNvs& nvsManager_;
    std::unique_ptr<IPresetManager> presetManager_;

    // DMX-specific API pointers
    ApiConfig* apiConfig_;
    ApiPresets* apiPresets_;
    ApiPresetValues* apiPresetValues_;

    void init_dmx_apis();
    void cleanup_dmx_apis();
    void register_dmx_endpoints();
    void register_endpoints_esp32();
    void register_endpoints_test();
};
