#pragma once

#include <QWebSocket>
#include <QString>
#include <QObject>

class WebSocketClient : public QObject
{
private:
    Q_OBJECT
    QWebSocket ws;
    QString uri = "";
    QString status = "Disconnected";
    int32_t pageViews = 0;
    int32_t uniqueVisitors = 0;
    int32_t avgSessionDuration = 0;
    bool    connected = false;

public:
    explicit WebSocketClient(QObject *parent = nullptr);
    /// @brief Sends get request on the web socket server.
    Q_INVOKABLE void    SendRequest();
    Q_INVOKABLE bool    IsConnected();
    Q_INVOKABLE QString PageViews();
    Q_INVOKABLE QString UniqueVisitors();
    Q_INVOKABLE QString AvgSessionDuration();
    Q_INVOKABLE QString GetStatus();
    Q_INVOKABLE QString GetURI();

public slots:
    /// @brief Connects to the specific server.
    Q_INVOKABLE void Connect(const QUrl& url);    
    /// @brief Apply actions on the opened connection.
    Q_INVOKABLE void OnOpen();
    /// @brief Apply action when text message recieved.
    Q_INVOKABLE void OnText(const QString& message);
    Q_INVOKABLE void OnClose();
};
