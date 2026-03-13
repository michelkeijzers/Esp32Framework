idf_component_register(SRCS "main.cpp" "master/master.cpp" "common/esp_now/esp_now_handler.cpp" "slaves/webserver_slave/project_dmx_controller/api_config.cpp" "slaves/webserver_slave/project_dmx_controller/api_presets.cpp" "slaves/webserver_slave/project_dmx_controller/api_status.cpp" "slaves/webserver_slave/project_dmx_controller/webserver_slave.cpp" 
                      "esp/EspHttpServer.cpp"
                      INCLUDE_DIRS "." "master" "esp")
