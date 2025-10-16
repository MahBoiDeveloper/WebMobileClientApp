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
    connected = true;
    qDebug() << "Соединение установлено";
}

void WebSocketClient::OnText(const QString& message)
{
    qDebug() << "Поступило сообщение:" << message;

    if (message.at(0) == '{')
    {
        QJsonParseError err;
        auto doc = QJsonDocument::fromJson(message.toUtf8(), &err);
        QJsonObject obj = doc.object();

        this->pageViews = obj["pageViews"].toInt();
        this->uniqueVisitors = obj["uniqueVisitors"].toInt();
        this->avgSessionDuration = obj["avgSessionDuration"].toInt();

        qDebug() << "PageViews = " << PageViews();
        qDebug() << "UniqueVisitors = " << UniqueVisitors();
        qDebug() << "AvgSessionDuration = " << AvgSessionDuration();
    }
}

void WebSocketClient::OnOpen()      { ws.sendTextMessage("Hello chat!"); }
void WebSocketClient::SendRequest() { ws.sendTextMessage("get"); }

bool WebSocketClient::IsConnected()           { return connected; }
QString WebSocketClient::PageViews()          { return QString::number(pageViews); }
QString WebSocketClient::UniqueVisitors()     { return QString::number(uniqueVisitors); }
QString WebSocketClient::AvgSessionDuration() { return QString::number(avgSessionDuration); }
