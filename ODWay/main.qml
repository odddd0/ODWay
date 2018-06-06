import QtQuick 2.9

Rectangle {
    height: 680
    width: 480
    gradient: Gradient {
        GradientStop{ position: 0; color: "#E5F2F6";}
        GradientStop{ position: 1; color: "#B1DAE7";}
    }

    LauncherList {
        id: ll
        anchors.fill: parent
        Component.onCompleted: {
            addExample("Time table", "Time List Show",  Qt.resolvedUrl("TableTime.qml"));
        }
    }
}
