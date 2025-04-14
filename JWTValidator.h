#ifndef JWTVALIDATOR_H
#define JWTVALIDATOR_H


#include <string>
#include <jwt.h> // Нужно установить библиотеку jwt-cpp

class JWTValidator {
public:
    static bool validate(const std::string& token) {
        try {
            // Здесь ваш секретный ключ для проверки JWT
            const std::string secret = "your-secret-key";

            // Верификация токена
            auto decoded = jwt_decode(token);

            // Проверка подписи
            auto verifier = jwt_verify()
                .allow_algorithm(jwt::algorithm::hs256{secret});

            verifier.verify(decoded);

            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }
};

#endif // JWTVALIDATOR_H
