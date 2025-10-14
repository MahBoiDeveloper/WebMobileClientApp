#pragma once

#include <QWebSocket>
#include <QObject>

class WebSocketClient : public QObject
{
private:
    Q_OBJECT
    QWebSocket ws;

public:
    inline static int32_t pageViews = 0;
    inline static int32_t uniqueVisitors = 0;
    inline static int32_t avgSessionDuration = 0;

public:
    explicit WebSocketClient(QObject *parent = nullptr);
    /// @brief Sends get request on the web socket server.
    void SendRequest();

public slots:
    /// @brief Connects to the specific server.
    void Connect(const QUrl& url);    
    /// @brief Apply actions on the opened connection.
    void OnOpen();
    /// @brief Apply action when text message recieved.
    void OnText(const QString& message);
};
