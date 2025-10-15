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
        text: "Connected to the ws://expserver.site:40000"
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
                opacity: 0.7
                radius: 10
                height: 80
                width: 80
                color: "#eb4d4b"    // красный
            }
            Rectangle
            {
                opacity: 0.7
                radius: 10
                height: 80
                width: 80
                color: "#16a085"    // зеленый
            }
            Rectangle
            {
                opacity: 0.7
                radius: 10
                height: 80
                width: 80
                color: "#0984e3"    // синий
            }
        }

        Column
        {
            spacing: 10
            Rectangle
            {
                opacity: 0.7
                radius: 10
                height: 80
                width: 80
                color: '#1c5e59'    // красный
            }
            Rectangle
            {
                opacity: 0.7
                radius: 10
                height: 80
                width: 80
                color: '#88783e'    // зеленый
            }
            Rectangle
            {
                opacity: 0.7
                radius: 10
                height: 80
                width: 80
                color: '#aa3897'    // синий
            }
        }
    }
}
