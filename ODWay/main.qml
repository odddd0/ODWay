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
        visible: dp.isOpen
        Component.onCompleted: {
            addExample("Time table", "",  Qt.resolvedUrl("TableTime.qml"));
        }
    }

    DigitalPicker {
        id: dp
        theKey: ""
//        noEcho: true
    }
}
