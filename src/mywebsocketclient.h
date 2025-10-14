#pragma once

#include <QWebSocket>
#include <QObject>

class WebSocketClient : public QObject
{
private:
    QWebSocket ws;
    Q_OBJECT
public:
    explicit WebSocketClient(QObject *parent = nullptr);

public slots:
    void OnOpen();
    void OnText(const QString &message);
    void Connect(const QUrl &url);
};
