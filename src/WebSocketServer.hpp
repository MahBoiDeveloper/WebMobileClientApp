#pragma once

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>

class WebSocketServer : public QObject
{
private:
    Q_OBJECT
    QWebSocketServer *wss;
    QList<QWebSocket*> clients;

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
    void onNewConnection();
    void onTextMessageReceived(const QString &message);
    void onClientDisconnected();
};
