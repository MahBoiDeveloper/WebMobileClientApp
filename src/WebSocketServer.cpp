#include <QDebug>
#include "WebSocketServer.hpp"

WebSocketServer::WebSocketServer(QObject *parent) :
    QObject(parent),
    wss(nullptr)
{
}

WebSocketServer::~WebSocketServer() { CloseServer(); }

void WebSocketServer::HostServer()
{
    wss = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);

    if (wss->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server started on port 1234";
        connect(wss, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
    } else {
        qDebug() << "Failed to start server";
    }
}

void WebSocketServer::CloseServer()
{
    foreach (QWebSocket* client, clients)
    {
        client->close();
        client->deleteLater();
    }

    clients.clear();

    if (wss)
        wss->close();
}

void WebSocketServer::onNewConnection()
{
    QWebSocket* client = wss->nextPendingConnection();

    connect(client, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(client, &QWebSocket::disconnected,        this, &WebSocketServer::onClientDisconnected);

    clients.append(client);
    emit clientConnected();
}

void WebSocketServer::onTextMessageReceived(const QString &message)
{
    qDebug() << "[SERVER] Поступило сообщение:" << message;

    if (message == "get")
    {
        foreach (QWebSocket *client, clients)
        {
            client->sendTextMessage(message);
        }
    }
}

void WebSocketServer::onClientDisconnected()
{
    QWebSocket* client = qobject_cast<QWebSocket *>(sender());
    
    if (client)
    {
        clients.removeAll(client);
        client->deleteLater();
        emit clientDisconnected();
    }
}
