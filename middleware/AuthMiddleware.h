#ifndef AUTHMIDDLEWARE_H
#define AUTHMIDDLEWARE_H

#include <drogon/drogon.h>

class AuthMiddleware : public drogon::HttpFilter<AuthMiddleware>
{
public:    
    void doFilter(const drogon::HttpRequestPtr& req,
                  drogon::FilterCallback&& fcb,
                  drogon::FilterChainCallback&& fccb) override;
};

#endif // AUTHMIDDLEWARE_H
