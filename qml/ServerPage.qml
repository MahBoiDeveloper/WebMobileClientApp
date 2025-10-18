import QtQuick 2.6
import Sailfish.Silica 1.0

Page {
    objectName: "serverPage"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: "v0.3"
        extraContent.children: [
            // IconButton {
            //     objectName: "aboutButton"
            //     icon.source: "image://theme/icon-m-about"
            //     anchors.verticalCenter: parent.verticalCenter

            //     onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            // }
        ]
    }
}
