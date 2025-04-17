#include <drogon/drogon.h>
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
            auto resp = HttpResponse::newHttpJsonResponse(result[0].toJson());
            callback(resp);
        },
        [callback](const drogon::orm::DrogonDbException& e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
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
