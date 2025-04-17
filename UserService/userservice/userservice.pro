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
        main.cpp
