#include "JWTValidator.h"


bool JWTValidator::validate(const std::string &token)
{
    try {
        // Здесь ваш секретный ключ для проверки JWT
        const std::string secret = "your-secret-key";

        // Верификация токена
        auto decoded = jwt::decode(token);

        // Проверка подписи
        auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secret});

        verifier.verify(decoded);

        return true;
    } catch (const std::exception& e) {
        std::cerr << "JWT validation failed: " << e.what() << std::endl;
        return false;
    }
}
