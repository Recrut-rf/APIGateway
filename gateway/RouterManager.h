#ifndef ROUTERMANAGER_H
#define ROUTERMANAGER_H

#include <drogon/drogon.h>
#include <drogon/HttpRequest.h>     // для HttpRequestPtr
#include <drogon/HttpResponse.h>    // для HttpResponsePtr
#include <drogon/HttpTypes.h>       // для HttpMethod


// RouterManager.h
class RouterManager
{
public:
    static RouterManager& getInstance();

    void addRoute(const std::string& path,
                  const drogon::HttpMethod& method,
                  std::function<void(const drogon::HttpRequestPtr&,
                                     std::function<void(const drogon::HttpResponsePtr&)>&&)> handler,
                  const std::vector<std::shared_ptr<drogon::HttpFilterBase>>& filters);

private:
    RouterManager() = default;
};


#endif // ROUTERMANAGER_H
