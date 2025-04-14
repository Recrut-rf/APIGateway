TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/include/jsoncpp
LIBS += -ljsoncpp

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
