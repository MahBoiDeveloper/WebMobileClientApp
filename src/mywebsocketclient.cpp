#include "mywebsocketclient.h"

#include <QDebug>

MyWebSocketClient::MyWebSocketClient(QObject *parent) : QObject(parent) {
    connect(&m_webSocket, &QWebSocket::connected, this, &MyWebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &MyWebSocketClient::onTextMessageReceived);
}

void MyWebSocketClient::connectToServer(const QUrl &url) {
    qDebug() << "Подключение к серверу WebSocket:" << url.toString();
    m_webSocket.open(url);
}

void MyWebSocketClient::onConnected() {
    qDebug() << "WebSocket соединение установлено";
    m_webSocket.sendTextMessage(QStringLiteral("Привет, сервер!"));
}

void MyWebSocketClient::onTextMessageReceived(const QString &message) {
    qDebug() << "Получено сообщение от сервера:" << message;
}
