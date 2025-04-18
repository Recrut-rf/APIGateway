#ifndef SERVICEREGISTRY_H
#define SERVICEREGISTRY_H

#include <map>
#include <string>
#include <drogon/HttpClient.h>

class ServiceRegistry
{
public:
    static ServiceRegistry& getInstance();

    void init();

    drogon::HttpClientPtr getServiceClient(const std::string& serviceName);

private:
    std::unordered_map<std::string, drogon::HttpClientPtr> serviceClients_;

    // Загрузка конфигурации сервисов
    void loadServicesConfig();

    // Инициализация соединений с сервисами
    void initializeServiceConnections();
};

#endif // SERVICEREGISTRY_H
