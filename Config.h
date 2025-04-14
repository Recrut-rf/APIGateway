#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct Config {
    static const std::string DB_HOST;
    static const std::string DB_PORT;
    static const std::string DB_NAME;
    static const std::string DB_USER;
    static const std::string DB_PASSWORD;

    // Другие константы конфигурации
    static const int SERVER_PORT;
    static const int THREAD_NUM;

    // Можно добавить методы для загрузки конфигурации
    static void loadConfig(const std::string& configFile);
};


#endif // CONFIG_H
