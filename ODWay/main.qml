import QtQuick 2.9

Rectangle {
    height: 640
    width: 480

    LauncherList {
        id: ll
        anchors.fill: parent
        Component.onCompleted: {
            addExample("Time table", "Uses all ImageParticle features",  Qt.resolvedUrl("TableTime.qml"));
        }
    }
}
