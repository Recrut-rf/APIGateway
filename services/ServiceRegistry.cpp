#include "ServiceRegistry.h"

ServiceRegistry &ServiceRegistry::getInstance()
{
    static ServiceRegistry instance;
    return instance;
}

void ServiceRegistry::init()
{
    loadServicesConfig();
    initializeServiceConnections();
}

drogon::HttpClientPtr ServiceRegistry::getServiceClient(const std::string &serviceName)
{
    auto it = serviceClients_.find(serviceName);
    if (it != serviceClients_.end()) {
        return it->second;
    }
    return nullptr;
}

void ServiceRegistry::loadServicesConfig() {

}

void initializeServiceConnections() {

}
