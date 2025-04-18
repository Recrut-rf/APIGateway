#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <memory>
#include <json/json.h>

class Config {
public:
    static Config& getInstance()
    {
        static Config instance;
        return instance;
    }

    void load(const std::string& filename);

    // Геттеры для настроек базы данных
    std::string getDbHost() const { return dbHost; }
    int getDbPort() const { return dbPort; }
    std::string getDbName() const { return dbName; }
    std::string getDbUser() const { return dbUser; }
    std::string getDbPassword() const { return dbPassword; }

    // Геттеры для настроек сервера
    int getServerPort() const { return serverPort; }
    int getServerThreads() const { return serverThreads; }

private:
    Config() = default; // приватный конструктор для синглтона

    // Запрещаем копирование и присваивание
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    // Поля для хранения настроек
    std::string dbHost;
    int dbPort;
    std::string dbName;
    std::string dbUser;
    std::string dbPassword;

    int serverPort;
    int serverThreads;
};


#endif // CONFIG_H
