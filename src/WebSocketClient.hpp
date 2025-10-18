#pragma once

#include <QWebSocket>
#include <QString>
#include <QObject>

class WebSocketClient : public QObject
{
    Q_OBJECT
private:
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
    /// @brief Checks if client is connected to the server.
    Q_INVOKABLE bool    IsConnected();
    /// @brief Returns current page views string value.
    Q_INVOKABLE QString PageViews();
    /// @brief Returns current unique visitors string value.
    Q_INVOKABLE QString UniqueVisitors();
    /// @brief Returns current page average session duration string value.
    Q_INVOKABLE QString AvgSessionDuration();
    /// @brief Returns client status.
    Q_INVOKABLE QString GetStatus();
    /// @brief Returns URI that used to send data.
    Q_INVOKABLE QString GetURI();

public slots:
    /// @brief Connects to the specific server.
    Q_INVOKABLE void Connect(const QUrl& url);    
    /// @brief Apply actions on the opened connection.
    Q_INVOKABLE void OnOpen();
    /// @brief Apply action when text message recieved.
    Q_INVOKABLE void OnText(const QString& message);
    /// @brief Apply action when connection was closed.
    Q_INVOKABLE void OnClose();
};
