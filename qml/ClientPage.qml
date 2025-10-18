import QtQuick 2.6
import Sailfish.Silica 1.0
import WebSocketClient 1.0
import WebSocketServer 1.0

// If you get M306 -- add Q_INVOKABLE
// https://stackoverflow.com/questions/31630078/c-class-exposed-to-qml-error-in-fashion-typeerror-property-of-object-is

ApplicationWindow
{
    objectName: "applicationWindow"
    initialPage: Qt.resolvedUrl("pages/MainPage.qml")
    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    // https://metanit.com/cpp/qt/5.2.php
    WebSocketClient { id: wsc }
    WebSocketServer { id: wss }

    Column
    {
        id: cLayout
        spacing: 10
        x: 60
        y: 150

        Button
        {
            id: btnServer
            visible: false
            width: 200
            height: 30
            color: '#ffffff';
            backgroundColor: '#441c7f'
            text: "Server Mode"
        }

        Label
        {
            id: lblHeader
            y: btnServer.y + btnServer.height + cLayout.spacing + 30
            text: wsc.GetStatus()
        }

        Row
        {
            id: rwBody
            spacing: cLayout.spacing

            Column
            {
                spacing: cLayout.spacing
                Rectangle
                {
                    id: rLeftRect
                    radius: 10
                    height: 80
                    width: 450
                    color: '#e3ff43'
                    Text
                    {
                        id: txtMain
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        font.family: "Consolas"
                        text: "Page Views:"
                    }
                }
                Rectangle
                {
                    opacity: rLeftRect.opacity
                    radius: rLeftRect.radius
                    color: rLeftRect.color
                    height: rLeftRect.height
                    width: rLeftRect.width
                    Text
                    {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        font.family: txtMain.font.family
                        text: "Unique Visitors:"
                    }
                }
                Rectangle
                {
                    opacity: rLeftRect.opacity
                    radius: rLeftRect.radius
                    color: rLeftRect.color
                    height: rLeftRect.height
                    width: rLeftRect.width
                    Text
                    {
                        anchors.fill: parent
                        anchors.leftMargin: 10
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        font.family: txtMain.font.family
                        text: "Avg. Session Duration:"
                    }
                }
            }

            Column
            {
                spacing: cLayout.spacing
                Rectangle
                {
                    id: rRightRect
                    opacity: rLeftRect.opacity
                    radius: rLeftRect.radius
                    color: rLeftRect.color
                    height: 80
                    width: 100
                    Text
                    {
                        id: txtPageViewsValue
                        opacity: txtMain.opacity
                        anchors.centerIn: parent
                        font.family: txtMain.font.family
                        text: "N/A"
                    }
                }
                Rectangle
                {
                    opacity: rRightRect.opacity
                    radius: rRightRect.radius
                    color: rRightRect.color
                    height: rRightRect.height
                    width: rRightRect.width
                    Text
                    {
                        id: txtUniqueVisitorsValue
                        opacity: txtMain.opacity
                        anchors.centerIn: parent
                        font.family: txtMain.font.family
                        text: "N/A"
                    }
                }
                Rectangle
                {
                    opacity: rRightRect.opacity
                    radius: rRightRect.radius
                    color: rRightRect.color
                    height: rRightRect.height
                    width: rRightRect.width
                    Text
                    {
                        id: txtAvgSessionDurationValue
                        opacity: txtMain.opacity
                        anchors.centerIn: parent
                        font.family: txtMain.font.family
                        text: "N/A"
                        onTextChanged: {
                            text = wsc.AvgSessionDurationValue
                        }
                    }
                }
            }
        }

        TextField
        {
            id: inpURI
            width: 500
            text: "ws://expserver.site:40000"
        }

        Row
        {
            spacing: cLayout.spacing
            Button
            {
                id: btnConnect
                width: btnServer.width
                height: btnServer.height
                color: btnServer.color;
                backgroundColor: btnServer.backgroundColor
                text: "Connect"

                onClicked: {
                    // Initilze connection
                    wsc.Connect(inpURI.text)
                    wsc.SendRequest()
                    lblHeader.text = wsc.GetStatus()

                    // Update data on the screen
                    txtPageViewsValue.text = wsc.PageViews()
                    txtUniqueVisitorsValue.text = wsc.UniqueVisitors()
                    txtAvgSessionDurationValue.text = wsc.AvgSessionDuration()

                    // Change style and text if connected
                    text = wsc.IsConnected ? "Connected" : "Connect"
                    backgroundColor = wsc.IsConnected ? '#ab23ab' : btnServer.backgroundColor

                    // Hide host button
                    btnHost.visible = false
                }
            }

            Button
            {
                id: btnGet
                width: btnServer.width
                height: btnServer.height
                color: btnServer.color;
                backgroundColor: btnServer.backgroundColor
                text: "Get Data"

                onClicked: {
                    wsc.SendRequest()
                    txtPageViewsValue.text = wsc.PageViews()
                    txtUniqueVisitorsValue.text = wsc.UniqueVisitors()
                    txtAvgSessionDurationValue.text = wsc.AvgSessionDuration()
                }
            }

            Button
            {
                id: btnHost
                width: btnServer.width
                height: btnServer.height
                color: btnServer.color;
                backgroundColor: btnServer.backgroundColor
                text: "Host"

                onClicked: {
                    // Starting the websocket server
                    wss.HostServer()

                    // Change style and text if hosted
                    text = true ? "Hosted" : "Host"
                    backgroundColor = true ? '#ab23ab' : btnServer.backgroundColor

                    // Hide client buttons
                    btnConnect.visible = false
                    btnGet.visible = false
                    lblHeader.text = wss.GetStatus()
                }
            }
        }
    }
}   
