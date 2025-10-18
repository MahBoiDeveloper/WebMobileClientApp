#include <string>
#include <random>
#include <QDebug>
#include "WebSocketServer.hpp"

std::random_device rd;  // Non-deterministic seed
std::mt19937 gen(rd()); // Mersenne Twister engine
std::uniform_int_distribution<> dist(100, 1000); // Range for integers
std::uniform_real_distribution<> dist_float(1.0, 300.0); // For session duration

WebSocketServer::WebSocketServer(QObject *parent) :
    QObject(parent),
    wss(nullptr)
{
}

WebSocketServer::~WebSocketServer() { CloseServer(); }

void WebSocketServer::HostServer()
{
    if (hosted)
        return;

    wss = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);

    if (wss->listen(QHostAddress::Any, port))
    {
        hosted = true;
        qDebug() << "[SERVER] Сервер запущен на адресе " << "locahost:" << port;
        connect(wss, &QWebSocketServer::newConnection, this, &WebSocketServer::OnNewConnection);
    }
    else
    {
        hosted = false;
        qDebug() << "[SERVER] Сервер не стартанул на адресе " << "locahost:" << port;
    }
}

bool WebSocketServer::IsHosted() { return hosted; }

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

void WebSocketServer::OnNewConnection()
{
    QWebSocket* client = wss->nextPendingConnection();

    connect(client, &QWebSocket::textMessageReceived, this, &WebSocketServer::OnTextMessageReceived);
    connect(client, &QWebSocket::disconnected,        this, &WebSocketServer::OnClientDisconnected);

    clients.append(client);
    emit clientConnected();
}

void WebSocketServer::OnTextMessageReceived(const QString &message)
{
    qDebug() << "[SERVER] Поступило сообщение:" << message;

    if (message == "get")
    {
        foreach (QWebSocket *client, clients)
        {
            // Generate random values
            int pageViews = dist(gen);
            int uniqueVisitors = dist(gen);
            double avgSessionDuration = dist_float(gen);

            // Page views per day (7 days)
            int pvPerDay[7];
            for (int& val : pvPerDay)
                val = dist(gen);

            QString request = QString("{\"pageViews\":") +
                    QString::number(pageViews) +
                    ",\"uniqueVisitors\":" + QString::number(uniqueVisitors) +
                    ",\"avgSessionDuration\":" + QString::number(avgSessionDuration, 'f', 2) +
                    ",\"pageViewsPerDay\":[" +
                    QString::number(pvPerDay[0]) + "," +
                    QString::number(pvPerDay[1]) + "," +
                    QString::number(pvPerDay[2]) + "," +
                    QString::number(pvPerDay[3]) + "," +
                    QString::number(pvPerDay[4]) + "," +
                    QString::number(pvPerDay[5]) + "," +
                    QString::number(pvPerDay[6]) +
                    "]}";

            client->sendTextMessage(request);
        }
    }
}

void WebSocketServer::OnClientDisconnected()
{
    QWebSocket* client = qobject_cast<QWebSocket *>(sender());

    if (client)
    {
        clients.removeAll(client);
        client->deleteLater();
        emit clientDisconnected();
    }
}
