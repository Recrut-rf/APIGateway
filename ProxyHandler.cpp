#include "ProxyHandler.h"
#include "services/ServiceRegistry.h"

void ProxyHandler::handleRequest(const drogon::HttpRequestPtr &req,
                                 std::function<void (const drogon::HttpResponsePtr &)> &&callback,
                                 const std::string &serviceName,
                                 const std::string &path)
{
    auto client = ServiceRegistry::getInstance().getServiceClient(serviceName);
    if (!client)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k503ServiceUnavailable);
        callback(resp);
        return;
    }

    auto request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(req->getMethod());
    request->setPath(path);

    // Копирование заголовков
    for (auto& header : req->headers())
    {
        request->addHeader(header.first, header.second);
    }

    // Отправка запроса
    client->sendRequest(request, [callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response)
    {
        if (result != drogon::ReqResult::Ok)
        {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k502BadGateway);
            callback(resp);
            return;
        }
        callback(response);
    });
}
