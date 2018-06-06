import QtQuick 2.9

Rectangle {
    height: 680
    width: 480

    LauncherList {
        id: ll
        anchors.fill: parent
        Component.onCompleted: {
            addExample("Time table", "Time List Show",  Qt.resolvedUrl("TableTime.qml"));
        }
    }
}
