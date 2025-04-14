#ifndef RATELIMITER
#define RATELIMITER

#include <drogon/drogon.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpFilter.h>
#include <drogon/HttpTypes.h>

class RateLimiter : public drogon::HttpFilter<RateLimiter> {
public:
    void doFilter(const drogon::HttpRequestPtr& req,
                  drogon::FilterCallback&& fcb,
                  drogon::FilterChainCallback&& fccb) override;

private:
    bool isRateLimited(const std::string& clientIP);
};

#endif // RATELIMITER
