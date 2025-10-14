#include <QFile>
#include <QDebug>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include "WebSocketClient.hpp"

WebSocketClient::WebSocketClient(QObject* parent) : QObject(parent)
{
    connect(&ws, &QWebSocket::connected,           this, &WebSocketClient::OnOpen);
    connect(&ws, &QWebSocket::textMessageReceived, this, &WebSocketClient::OnText);
}

void WebSocketClient::Connect(const QUrl& url)
{
    qDebug() << "Подключение к серверу WebSocket:" << url.toString() << "...";
    ws.open(url);
    qDebug() << "Соединение установлено";
}

void WebSocketClient::OnOpen() { ws.sendTextMessage("Hello chat!"); }

void WebSocketClient::OnText(const QString& message)
{
    qDebug() << "Поступило сообщение:" << message;

    if (message.at(0) == '{')
    {
        QJsonParseError err;
        auto doc = QJsonDocument::fromJson(message.toUtf8(), &err);
        QJsonObject obj = doc.object();

        qDebug() << "pageViews = " << QString::number(pageViews = obj["pageViews"].toInt());
        qDebug() << "uniqueVisitors = " << QString::number(uniqueVisitors = obj["uniqueVisitors"].toInt());
        qDebug() << "avgSessionDuration = " << QString::number(avgSessionDuration = obj["avgSessionDuration"].toInt());
    }

}

void WebSocketClient::SendRequest() { ws.sendTextMessage("get"); }
