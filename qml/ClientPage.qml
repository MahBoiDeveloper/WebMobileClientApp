import QtQuick 2.6
import Sailfish.Silica 1.0
import WebSocketClient 1.0

// If you get M306 -- add Q_INVOKABLE
// https://stackoverflow.com/questions/31630078/c-class-exposed-to-qml-error-in-fashion-typeerror-property-of-object-is

ApplicationWindow
{
    objectName: "applicationWindow"
    initialPage: Qt.resolvedUrl("pages/MainPage.qml")
    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    // https://metanit.com/cpp/qt/5.2.php
    WebSocketClient
    {
        id: wsc
    }

    Label
    {
        id: lblHeader
        x: 60
        y: 150
        text: wsc.GetStatus()
    }

    Row
    {
        id: rwBody
        x: lblHeader.x
        y: lblHeader.y + 150
        spacing: 10

        Column
        {
            spacing: 10
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
            spacing: 10
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

    Row
    {
        x: rwBody.x
        y: rwBody.y + 350
        spacing: rwBody.spacing
        Column
        {
            Button
            {
                id: btnConnect
                width: 200
                height: 30
                color: '#ffffff';
                text: "Connect"
                backgroundColor: '#441c7f'

                onClicked: {
                    wsc.Connect("ws://expserver.site:40000")
                    wsc.SendRequest()
                    lblHeader.text = wsc.GetStatus()

                    txtPageViewsValue.text = wsc.PageViews()
                    txtUniqueVisitorsValue.text = wsc.UniqueVisitors()
                    txtAvgSessionDurationValue.text = wsc.AvgSessionDuration()

                    text = "Connected"
                    color = '#000000'
                    backgroundColor = '#ab23ab'
                }
            }
        }

        Column
        {
            Button
            {
                id: btnGet
                width: 200
                height: 30
                color: '#ffffff';
                text: "Get Data"

                onClicked: {
                    wsc.SendRequest()
                    txtPageViewsValue.text = wsc.PageViews()
                    txtUniqueVisitorsValue.text = wsc.UniqueVisitors()
                    txtAvgSessionDurationValue.text = wsc.AvgSessionDuration()
                }
                backgroundColor: '#441c7f'
            }
        }
    }    
}
