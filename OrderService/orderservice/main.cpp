#include <drogon/drogon.h>
#include <drogon/HttpResponse.h>
#include <json/json.h>

using namespace drogon;

void createOrder(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
    auto json = req->getJsonObject();
    if (!json) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto dbClient = app().getDbClient();
    int userId = (*json)["user_id"].asInt();
    std::string items = (*json)["items"].asString();

    dbClient->execSqlAsync(
        "INSERT INTO orders (user_id, items) VALUES ($1, $2) RETURNING id",
        [callback](const drogon::orm::Result& result) {
            Json::Value ret;
            ret["id"] = result[0]["id"].as<int>(); // Предполагая, что возвращается столбец 'id'

            auto resp = HttpResponse::newHttpJsonResponse(ret);
            callback(resp);
        },
        [callback](const drogon::orm::DrogonDbException& e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            LOG_ERROR << "Database error: " << e.base().what();
            callback(resp);
        },
        userId, items);
}

int main() {
    app().loadConfigFile("config.json");
    app().registerHandler("/orders", &createOrder, {Post});
    app().run();
    return 0;
}
