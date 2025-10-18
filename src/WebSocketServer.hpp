#pragma once

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>

class WebSocketServer : public QObject
{
    Q_OBJECT
private:
    QWebSocketServer *wss;
    QList<QWebSocket*> clients;
    uint16_t port = 40000;

public:
    explicit WebSocketServer(QObject *parent = nullptr);
    ~WebSocketServer();

    void HostServer();
    void CloseServer();

signals:
    void newMessageReceived(const QString &message);
    void clientConnected();
    void clientDisconnected();

private slots:
    void OnNewConnection();
    void OnTextMessageReceived(const QString &message);
    void OnClientDisconnected();
};
