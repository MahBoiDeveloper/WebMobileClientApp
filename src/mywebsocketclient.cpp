#include <QDebug>
#include "WebSocketClient.hpp"

WebSocketClient::WebSocketClient(QObject *parent) : QObject(parent)
{
    connect(&ws, &QWebSocket::connected,           this, &WebSocketClient::OnOpen);
    connect(&ws, &QWebSocket::textMessageReceived, this, &WebSocketClient::OnText);
}

void WebSocketClient::Connect(const QUrl &url)
{
    qDebug() << "Подключение к серверу WebSocket:" << url.toString();
    ws.open(url);
}

void WebSocketClient::OnOpen()
{
    qDebug() << "WebSocket соединение установлено";
    ws.sendTextMessage(QStringLiteral("get"));
}

void WebSocketClient::OnText(const QString &message)
{
    qDebug() << "Получено сообщение от сервера:" << message;
}
