#include <drogon/drogon.h>
using namespace drogon;

void createUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
    auto json = req->getJsonObject();
    if (!json) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto dbClient = app().getDbClient();
    std::string name = (*json)["name"].asString();
    std::string email = (*json)["email"].asString();

    dbClient->execSqlAsync(
        "INSERT INTO users (name, email) VALUES ($1, $2) RETURNING id",
        [callback](const drogon::orm::Result& result) {
//            auto resp = HttpResponse::newHttpJsonResponse(result[0].toJson());
//            callback(resp);
        Json::Value ret;
        ret["id"] = result[0]["id"].as<int>(); // Предполагая, что возвращается столбец 'id'

        auto resp = HttpResponse::newHttpJsonResponse(ret);
        callback(resp);
        },
        [callback](const drogon::orm::DrogonDbException& e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
        },
        name, email);
}

void deleteUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
    auto userId = req->getParameter("id");
    auto dbClient = app().getDbClient();

    dbClient->execSqlAsync(
        "DELETE FROM users WHERE id = $1",
        [callback](const drogon::orm::Result& result) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k200OK);
            callback(resp);
        },
        [callback](const drogon::orm::DrogonDbException& e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
        },
        userId);
}

int main() {
    app().loadConfigFile("config.json");
    app().registerHandler("/users", &createUser, {Post});
    app().registerHandler("/users/{id}", &deleteUser, {Delete});
    app().run();
    return 0;
}
