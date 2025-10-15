#include <QFile>
#include <QDebug>
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
    Connected = true;
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

        PageViews = QString::number(pageViews = obj["pageViews"].toInt());
        UniqueVisitors = QString::number(uniqueVisitors = obj["uniqueVisitors"].toInt());
        AvgSessionDuration = QString::number(avgSessionDuration = obj["avgSessionDuration"].toInt());

        qDebug() << "PageViews = " << PageViews;
        qDebug() << "UniqueVisitors = " << UniqueVisitors;
        qDebug() << "AvgSessionDuration = " << AvgSessionDuration;
    }

}

void WebSocketClient::SendRequest() { ws.sendTextMessage("get"); }
