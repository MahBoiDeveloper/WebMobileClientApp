TARGET = ru.auroraos.websocketapp

CONFIG += \
    c++17 \
    auroraapp \

QT += core gui qml quick network dbus svg websockets

PKGCONFIG += \

SOURCES += \
    src/WebSocketServer.cpp \
    src/main.cpp \
    src/WebSocketClient.cpp \

HEADERS += \
    src/WebSocketClient.hpp \
    src/WebSocketServer.hpp

DISTFILES += \
    qml/ClientPage.qml \
    rpm/ru.auroraos.websocketapp.spec \
    qml/cover/DefaultCoverPage.qml \
    qml/pages/AboutPage.qml \
    qml/pages/MainPage.qml \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-CLAUSE.md \
    README.md \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.websocketapp.ts \
    translations/ru.auroraos.websocketapp-ru.ts \
