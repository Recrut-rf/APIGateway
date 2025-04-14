#include <iostream>
#include "Config.h"

//const std::string Config::DB_HOST = "localhost";
//const std::string Config::DB_PORT = "5432";
//const std::string Config::DB_NAME = "mydb";
//const std::string Config::DB_USER = "postgres";
//const std::string Config::DB_PASSWORD = "password";

//const int Config::SERVER_PORT = 8080;
//const int Config::THREAD_NUM = 4;

#include <fstream>
#include <stdexcept>

void Config::load(const std::string& filename) {
    try {
        // Открываем файл
        std::ifstream configFile(filename);
        if (!configFile.is_open()) {
            throw std::runtime_error("Unable to open config file: " + filename);
        }

        // Парсим JSON
        Json::Value config;
        Json::CharReaderBuilder readerBuilder;
        std::string errs;
        if (!Json::parseFromStream(readerBuilder, configFile, &config, &errs)) {
            std::cerr << "Ошибка парсинга JSON: " << errs << std::endl;
        }

        // Загружаем настройки базы данных
        // Извлекаем данные из JSON
        dbHost = config["database"]["host"].asString();
        dbPort = config["database"]["port"].asInt();
        dbName = config["database"]["name"].asString();
        dbUser = config["database"]["user"].asString();
        dbPassword = config["database"]["password"].asString();

        serverPort = config["server"]["port"].asInt();
        serverThreads = config["server"]["threads"].asInt();

    } catch (const Json::Exception& e) {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw std::runtime_error("Config loading error: " + std::string(e.what()));
    }
}
