#include <QtQuick>
#include <auroraapp.h>
#include "WebSocketClient.hpp"
#include "WebSocketServer.hpp"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    QScopedPointer<QQuickView> view(Aurora::Application::createView());

    qmlRegisterType<WebSocketClient>("WebSocketClient", 1, 0, "WebSocketClient");

    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/ClientPage.qml")));
    view->show();

    // WebSocketClient client;
    // client.Connect(QUrl("ws://expserver.site:40000"));
    // client.SendRequest();

    return application->exec();
}
