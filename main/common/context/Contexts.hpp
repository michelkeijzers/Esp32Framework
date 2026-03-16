#pragma once

class IEspLittleFs;
class IEspHttpServer;
class IEspNvs;
class IEspLogger;

class IApiStatus;
class IApiNodes;
class IApiSystem;
class IApiFirmware;
class IApiSecurity;
class IApiLogging;

struct EspContexts
{
    IEspLittleFs &espLittleFs;
    IEspHttpServer &espHttpServer;
    IEspNvs &espNvs;
    IEspLogger &espLogger;
};

struct CommonApiContexts
{
    IApiStatus &apiStatus;
    IApiNodes &apiNodes;
    IApiSystem &apiSystem;
    IApiFirmware &apiFirmware;
    IApiSecurity &apiSecurity;
    IApiLogging &apiLogging;
};

struct Contexts
{
    EspContexts &espContexts;
    CommonApiContexts &commonApiContexts;
};
