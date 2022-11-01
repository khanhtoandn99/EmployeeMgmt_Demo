TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Mq/MqHandler.cpp \
        Service/AvnDeploy.cpp \
        Service/AvnService.cpp \
        main.cpp

HEADERS += \
    Mq/MqHandler.h \
    Service/AvnDeploy.h \
    Service/AvnService.h \
    common.h \
    common_ipc.h
