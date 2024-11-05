TARGET = ru.auroraos.webSocket

CONFIG += auroraapp

QT += core gui qml quick network dbus svg #websockets

PKGCONFIG += \




LIBS += -Llibs -lqt5websockets

INCLUDEPATH += libs/qtwebsockets/include/QtWebSockets
INCLUDEPATH += libs/qtwebsockets/include


SOURCES += \
    src/main.cpp \
    src/mywebsocketclient.cpp

HEADERS += \
    src/mywebsocketclient.h

DISTFILES += \
    rpm/ru.auroraos.webSocket.spec \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-CLAUSE.md \
    README.md \
    qml/webSocket.qml \
    qml/cover/DefaultCoverPage.qml \
    qml/pages/AboutPage.qml \
    qml/pages/MainPage.qml \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.webSocket.ts \
    translations/ru.auroraos.webSocket-ru.ts \
