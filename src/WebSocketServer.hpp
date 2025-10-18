#pragma once

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>

class WebSocketServer : public QObject
{
    Q_OBJECT
private:
    QWebSocketServer* wss;
    QList<QWebSocket*> clients;
    uint16_t port = 40000;
    bool hosted = false;

public:
    explicit WebSocketServer(QObject *parent = nullptr);
    ~WebSocketServer();

    Q_INVOKABLE void HostServer();
    Q_INVOKABLE void CloseServer();

    Q_INVOKABLE bool IsHosted();

signals:
    Q_INVOKABLE void newMessageReceived(const QString &message);
    Q_INVOKABLE void clientConnected();
    Q_INVOKABLE void clientDisconnected();

private slots:
    Q_INVOKABLE void OnNewConnection();
    Q_INVOKABLE void OnTextMessageReceived(const QString &message);
    Q_INVOKABLE void OnClientDisconnected();
};
