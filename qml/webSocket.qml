import QtQuick 2.0
import Sailfish.Silica 1.0

ApplicationWindow
{
    objectName: "applicationWindow"
    initialPage: Qt.resolvedUrl("pages/MainPage.qml")
    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Label
    {
        x: 60
        y: 150
        text: qsTr("Connected to the ws://expserver.site:40000")
    }
    Row
    {
        x: 100
        y: 200
        spacing: 10

        Column
        {
            spacing: 10
            Rectangle
            {
                id: rLeftRect
                opacity: 1
                radius: 10
                height: 80
                width: 350
                color: '#e3ff43'    // красный
                Text
                {
                    id: txtMain
                    opacity: 1
                    anchors.centerIn: parent
                    font.family: "Consolas"
                    text: "pageViews"
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
                    opacity: txtMain.opacity
                    anchors.centerIn: parent
                    font.family: txtMain.font.family
                    text: "uniqueVisitors"
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
                    opacity: txtMain.opacity
                    anchors.centerIn: parent
                    font.family: txtMain.font.family
                    text: "avgSessionDuration"
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
                width: 80
                Text
                {
                    id: txtPageViewsValue
                    opacity: txtMain.opacity
                    anchors.centerIn: parent
                    font.family: txtMain.font.family
                    text: "asd"
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
                    text: "asd"
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
                    id: avgSessionDuration
                    opacity: txtMain.opacity
                    anchors.centerIn: parent
                    font.family: txtMain.font.family
                    text: "asd"
                }
            }
        }
    }
}
