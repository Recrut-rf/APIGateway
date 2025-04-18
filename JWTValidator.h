#ifndef JWTVALIDATOR_H
#define JWTVALIDATOR_H


#include <string>
#include <jwt-cpp/jwt.h>

class JWTValidator
{
public:
    static bool validate(const std::string& token);
};

#endif // JWTVALIDATOR_H
