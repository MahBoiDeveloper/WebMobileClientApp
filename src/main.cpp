#include <auroraapp.h>
#include <QtQuick>
#include "mywebsocketclient.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("webSocket"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/webSocket.qml")));
    view->show();

    WebSocketClient client;
    client.Connect(QUrl(QStringLiteral("ws://expserver.site:40000")));

    return application->exec();
}
