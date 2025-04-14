#include "AuthMiddleware.h"
#include "JWTValidator.h"

void AuthMiddleware::doFilter(const drogon::HttpRequestPtr &req,
                              drogon::FilterCallback &&fcb,
                              drogon::FilterChainCallback &&fccb)
{
    // Проверка JWT токена
    auto auth = req->getHeader("Authorization");
    if (auth.empty()) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        fcb(resp);
        return;
    }

    try {
        auto token = auth.substr(7); // Remove "Bearer "
        if (JWTValidator::validate(token)) {
            fccb();
            return;
        }
    } catch (const std::exception& e) {
        // Обработка ошибок
    }

    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k401Unauthorized);
    fcb(resp);
}
