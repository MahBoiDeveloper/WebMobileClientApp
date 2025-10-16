#pragma once

#include <QWebSocket>
//#include <QWebSocketServer>
#include <QString>
#include <QObject>

class WebSocketServer : public QObject
{
private:
    Q_OBJECT
//    QWebSocketServer wss;
public:
    explicit WebSocketServer(QObject *parent = nullptr);
};

