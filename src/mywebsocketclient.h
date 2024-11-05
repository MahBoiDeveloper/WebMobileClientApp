#ifndef MYWEBSOCKETCLIENT_H
#define MYWEBSOCKETCLIENT_H


#pragma once

#include <QWebSocket>
#include <QObject>

class MyWebSocketClient : public QObject {
    Q_OBJECT
public:
    explicit MyWebSocketClient(QObject *parent = nullptr);

public slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);

    void connectToServer(const QUrl &url);

private:
    QWebSocket m_webSocket;
};

#endif // MYWEBSOCKETCLIENT_H
