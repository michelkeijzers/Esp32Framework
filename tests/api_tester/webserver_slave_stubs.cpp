// Test-only stubs for WebserverSlave base class
// These are minimal implementations for linking tests without including ESP firmware headers

class WebserverSlave;
class IEspLittleFs;
class IEspHttpServer;
class IEspLogger;

class ApiStatus;
class ApiNodes;
class ApiSystem;
class ApiFirmware;
class ApiSecurity;
class ApiLogging;

// Forward declare the init function  
extern void WebserverSlave_init_generic_apis_stub(WebserverSlave* pthis);

// Slim stub implementation that doesn't require ESP headers
namespace {
    
void WebserverSlave_init_generic_apis_impl(WebserverSlave* pthis)
{
    // Stub - initialize API pointers to null for testing
    // Real impl is in common/WebserverSlave.cpp for production
}

void WebserverSlave_cleanup_generic_apis_impl(WebserverSlave* pthis)  
{
    // Stub - cleanup API pointers for testing
    // Real impl is in common/WebserverSlave.cpp for production
}

} // namespace

// Weaksymbol implementations that can be overridden by real common/WebserverSlave.cpp if linked
extern "C" __declspec(selectany) void WebserverSlave_init_generic_apis = &WebserverSlave_init_generic_apis_impl;
extern "C" __declspec(selectany) void WebserverSlave_cleanup_generic_apis = &WebserverSlave_cleanup_generic_apis_impl;
