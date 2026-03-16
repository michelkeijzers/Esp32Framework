# Folder Structure

## Production Code Structure

```
main/
    common/
        esp/
            esp_error/
                esp_error_if.hpp 
            esp_filesystem/
                esp_littlefs_if.h, esp_spiffs-if.h, IEspLittleFs.hpp, EspLittleFs.hpp/cpp
            esp_http_server/
                esp_http_server_if.hpp, IEspHttpServer.hpp, EspHttpServer.hpp/cpp
            esp_now/
                esp_now_if.hpp, IEspNow.hpp, EspNow.hpp/cpp
            esp_logger/
                esp_logger_if.hpp, IEspLogger.hpp, EspLogger.hpp/cpp
            esp_nvs/
                esp_nvs_if.hpp, IEspNvs.hpp, EspNvs.hpp/cpp
        tasks/
            esp_now_task/
                EspNowTask.hpp/cpp
            status_task/
                StatusTask.hpp/cpp
            nvs_task/
                NvsTask.hpp/cpp
            ota_task/
                OtaTask.hpp/cpp
        master/
            Master.hpp/cpp
            MasterTask 
                MasterTask.hpp/cpp
        slaves/
            webserver_slave/
                webserver_slave_task/
                    WebserverSlaveTask.hpp/cpp
                http_task
                    HttpTask.hpp/cpp
                    apis/
                        ApiSecurity.hpp/cpp
                        ApiStatus.hpp/cpp
                        ApiOta.hpp/cpp
                        ...
                    website/
                        status.html
                        logging.html
                        nodes.html
                        ...
    projects
        dmx_controller/ (webserver slave implementation)
            IDmxControllerWebserverSlave.hpp
            DmxControllerWebserverSlave.hpp/cpp
            preset_task
                Presets.hpp/cpp
                Preset.hpp/cpp
            http_task
                IDmxControllerHttpTask.hpp
                DmxControllerHttpTask.hpp/cpp
                website
                    index.html
                    control.html
                    configuration.html
                    custom.css
```

## Tests 

Same structure.

> This structure keeps production and test code organized, maintainable, and easy to navigate. Each task/class has its own folder, and tests mirror the production structure for clarity.