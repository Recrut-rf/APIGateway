#include "RouterManager.h"
#include <utility>

RouterManager &RouterManager::getInstance()
{
    static RouterManager instance;
    return instance;
}

void RouterManager::addRoute(const std::string &path,
                             const drogon::HttpMethod &method,
                             std::function<void (const drogon::HttpRequestPtr &, std::function<void (const drogon::HttpResponsePtr &)> &&)> handler)
{
    drogon::app().registerHandler(
                path,
                method,
                [handler = std::move(handler)](const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
        handler(req, std::move(callback));
    });
}

