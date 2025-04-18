#include <iostream>
#include "Config.h"
#include <fstream>
#include <stdexcept>

void Config::load(const std::string& filename)
{
    try
    {
        // Открываем файл
        std::ifstream configFile(filename);
        if (!configFile.is_open())
        {
            throw std::runtime_error("Unable to open config file: " + filename);
        }

        // Парсим JSON
        Json::Value config;
        Json::CharReaderBuilder readerBuilder;
        std::string errs;
        if (!Json::parseFromStream(readerBuilder, configFile, &config, &errs))
        {
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

    } catch (const Json::Exception& e)
    {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    } catch (const std::exception& e)
    {
        throw std::runtime_error("Config loading error: " + std::string(e.what()));
    }
}
