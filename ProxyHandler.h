#ifndef PROXYHANDLER_H
#define PROXYHANDLER_H
#include <functional>
#include <string>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

class ProxyHandler
{
public:
    static void handleRequest(const drogon::HttpRequestPtr& req,
                              std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                              const std::string& serviceName,
                              const std::string& path);
};

#endif // PROXYHANDLER_H
