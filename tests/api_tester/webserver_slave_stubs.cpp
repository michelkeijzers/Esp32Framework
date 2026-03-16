// Test-only stubs for Webserver base class
// These are minimal implementations for linking tests without including ESP firmware headers

class Webserver;
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
extern void Webserver_init_generic_apis_stub(Webserver* pthis);

// Slim stub implementation that doesn't require ESP headers
namespace {
    
void Webserver_init_generic_apis_impl(Webserver* pthis)
{
    // Stub - initialize API pointers to null for testing
    // Real impl is in webserver_task/Webserver.cpp for production
}

void Webserver_cleanup_generic_apis_impl(Webserver* pthis)
{
    // Stub - cleanup API pointers for testing
    // Real impl is in webserver_task/Webserver.cpp for production
}

} // namespace

// Weaksymbol implementations that can be overridden by real webserver_task/Webserver.cpp if linked
extern "C" __declspec(selectany) void Webserver_init_generic_apis = &Webserver_init_generic_apis_impl;
extern "C" __declspec(selectany) void Webserver_cleanup_generic_apis = &Webserver_cleanup_generic_apis_impl;
