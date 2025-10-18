#include <QJsonObject>
#include <QJsonDocument>
#include <QAbstractSocket>
#include "WebSocketClient.hpp"

WebSocketClient::WebSocketClient(QObject* parent) : QObject(parent)
{
    connect(&ws, &QWebSocket::connected,           this, &WebSocketClient::OnOpen);
    connect(&ws, &QWebSocket::textMessageReceived, this, &WebSocketClient::OnText);
    connect(&ws, &QWebSocket::disconnected,        this, &WebSocketClient::OnClose);
}

void WebSocketClient::Connect(const QUrl& url)
{
    if (connected)
        return;

    qDebug() << "[CLIENT] Подключение к серверу WebSocket:" << url.toString() << "...";
    ws.open(url);

    qDebug() << "[CLIENT] Соединение установлено";
    connected = true;
    status = QString("Connected to ") + url.toString();
}

void WebSocketClient::OnText(const QString& message)
{
    qDebug() << "[CLIENT] Поступило сообщение:" << message;

    if (message.at(0) == '{')
    {
        uri = message;

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

void WebSocketClient::OnClose()
{
    qDebug() << "[CLIENT] Соединение закрыто";
    status = ws.errorString();
}

void WebSocketClient::OnOpen()      { SendRequest(); }
void WebSocketClient::SendRequest() { ws.sendTextMessage("get"); }

bool WebSocketClient::IsConnected()           { return connected; }
QString WebSocketClient::GetStatus()          { return status; }
QString WebSocketClient::GetURI()             { return uri; }
QString WebSocketClient::PageViews()          { return QString::number(pageViews); }
QString WebSocketClient::UniqueVisitors()     { return QString::number(uniqueVisitors); }
QString WebSocketClient::AvgSessionDuration() { return QString::number(avgSessionDuration); }
