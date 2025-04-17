#include <drogon/drogon.h>
#include "gateway/RouterManager.h"
#include "middleware/AuthMiddleware.h"
#include "middleware/RateLimiter.h"
#include "services/ServiceRegistry.h"
#include "config/Config.h"


int main() {
    // Загрузка конфигурации
    Config::getInstance().load("config.json");

    // Инициализация сервисов
    ServiceRegistry::getInstance().init();

    // Настройка сервера
    drogon::app()
            .setLogPath("./")
            .setLogLevel(trantor::Logger::kWarn)
            .addListener("0.0.0.0", 8080)
            .setThreadNum(16)
            .enableRunAsDaemon()
            .enableRelaunchOnError();

    // Регистрация middleware
    auto &router = RouterManager::getInstance();

    // Добавляем маршруты с нужными фильтрами
    router.addRoute("/secure", drogon::Get,
                    [](const drogon::HttpRequestPtr &req,
                    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
        // Обработчик
    },
    {std::make_shared<AuthMiddleware>(), std::make_shared<RateLimiter>()}
    );

    // Запуск сервера
    drogon::app().run();
    return 0;
}
