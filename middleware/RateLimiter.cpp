#include "RateLimiter.h"

void RateLimiter::doFilter(const drogon::HttpRequestPtr &req, drogon::FilterCallback &&fcb, drogon::FilterChainCallback &&fccb)
{
    auto clientIP = req->getPeerAddr().toIp();

    if (isRateLimited(clientIP))
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k429TooManyRequests);
        fcb(resp);
        return;
    }

    fccb();
}

bool RateLimiter::isRateLimited(const std::string &clientIP)
{
    // Реализация rate limiting с использованием Redis
    return false;
}
