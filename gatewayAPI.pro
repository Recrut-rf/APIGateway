TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

# Пути к заголовочным файлам
INCLUDEPATH += /usr/include/jsoncpp
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/include/postgresql

# Библиотеки
LIBS += -L/usr/local/lib \
        -ldrogon \
        -ltrantor \
        -ljsoncpp \
        -lssl \
        -lcrypto \
        -lz \
        -luuid \
        -lpthread \
        -ldl \
        -lpq

SOURCES += \
        CircuitBreaker.cpp \
        JWTValidator.cpp \
        config/Config.cpp \
        LoadBalancer.cpp \
        ProxyHandler.cpp \
        gateway/RouterManager.cpp \
        main.cpp \
        middleware/AuthMiddleware.cpp \
        middleware/RateLimiter.cpp \
        services/ServiceRegistry.cpp

HEADERS += \
    CircuitBreaker.h \
    JWTValidator.h \
    config/Config.h \
    LoadBalancer.h \
    ProxyHandler.h \
    gateway/RouterManager.h \
    middleware/AuthMiddleware.h \
    middleware/RateLimiter.h \
    services/ServiceRegistry.h
