#include "RouterManager.h"
#include <utility>

RouterManager &RouterManager::getInstance()
{
    static RouterManager instance;
    return instance;
}

void RouterManager::addRoute(const std::string& path,
                             const drogon::HttpMethod& method,
                             std::function<void(const drogon::HttpRequestPtr&,
                                                std::function<void(const drogon::HttpResponsePtr&)>&&)> handler,
                             const std::vector<std::shared_ptr<drogon::HttpFilterBase>>& filters)
{
    using namespace drogon;

    // Создаем shared_ptr для безопасного разделения состояния
    auto sharedState = std::make_shared<
            std::tuple<
            std::function<void(const HttpRequestPtr&, std::function<void(const HttpResponsePtr&)>&&)>,
            std::vector<std::shared_ptr<HttpFilterBase>>
            >>(std::move(handler), filters);

    auto handlerWithFilters = [sharedState](const HttpRequestPtr& req,
            std::function<void(const HttpResponsePtr&)>&& callback)
    {
        auto& [handler, filters] = *sharedState;

                // Функция для выполнения цепочки фильтров
                std::function<void(size_t)> applyFilters;

                applyFilters = [&, req, callback = std::move(callback)](size_t index) mutable {
            if (index >= filters.size()) {
                // Все фильтры пройдены - вызываем основной обработчик
                handler(req, std::move(callback));
                return;
            }

            // Применяем текущий фильтр
            filters[index]->doFilter(
                        req,
                        [callback](const HttpResponsePtr& resp) {
                // Обработка отказа фильтра
                callback(resp);
            },
            [&, index](auto&&...) {
                // Фильтр passed - переходим к следующему
                applyFilters(index + 1);
            }
            );
        };

        // Начинаем цепочку с первого фильтра
        applyFilters(0);
    };

    // Регистрируем обработчик
    app().registerHandler(
                path,
                std::move(handlerWithFilters),
    {method},
                "RouterManager"
                );
}

