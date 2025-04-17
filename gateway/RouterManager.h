#ifndef ROUTERMANAGER_H
#define ROUTERMANAGER_H

#include <drogon/drogon.h>
#include <drogon/HttpRequest.h>     // для HttpRequestPtr
#include <drogon/HttpResponse.h>    // для HttpResponsePtr
#include <drogon/HttpTypes.h>       // для HttpMethod


// RouterManager.h
class RouterManager {
public:
    static RouterManager& getInstance();


//    template<typename T>
//    void registerMiddleware() {
//        drogon::app().registerFilter(std::make_shared<T>());
//    }

//    template<typename T>
//    void registerMiddleware() {
//        // Проверяем, что T - это кастомный фильтр
//        static_assert(std::is_base_of_v<drogon::HttpFilter<T>, T>,
//                     "Only custom HttpFilter derivatives can be registered");
//        drogon::app().registerFilter(std::make_shared<T>());
//    }

//    void addRoute(const std::string& path,
//                  const drogon::HttpMethod& method,
//                  std::function<void(const drogon::HttpRequestPtr&,
//                                     std::function<void(const drogon::HttpResponsePtr&)>&&)> handler);

    void addRoute(const std::string& path,
                  const drogon::HttpMethod& method,
                  std::function<void(const drogon::HttpRequestPtr&,
                                   std::function<void(const drogon::HttpResponsePtr&)>&&)> handler,
                  const std::vector<std::shared_ptr<drogon::HttpFilterBase>>& filters);

private:
    RouterManager() = default;
};


#endif // ROUTERMANAGER_H
