import QtQuick 2.0

Rectangle {
    id: bar
    visible: height > 0
    anchors.top: parent.top
    width: parent.width
    height: activePageCount > 0 ? 40 : 0

    signal rightBtnClicked

    Behavior on height {
        NumberAnimation {
            duration: 300
        }
    }

    Rectangle {
        height: 1
        color: "#ccc"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        height: 1
        color: "#fff"
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right
    }

    gradient: Gradient {
        GradientStop { position: 0 ; color: "#eee" }
        GradientStop { position: 1 ; color: "#ccc" }
    }

    Image {
        id: back
        source: "images/back.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 2
        anchors.left: parent.left
        anchors.leftMargin: 16

        MouseArea {
            hoverEnabled: true
            anchors.centerIn: parent
            width: 38
            height: 31
            anchors.verticalCenterOffset: -1
            enabled: activePageCount > 0
            onClicked: {
                pageContainer.children[pageContainer.children.length - 1].exit()
            }
            Rectangle {
                anchors.fill: parent
                opacity: parent.pressed ? 1 : 0
                Behavior on opacity { NumberAnimation{ duration: 100 }}
                gradient: Gradient {
                    GradientStop { position: 0 ; color: "#22000000" }
                    GradientStop { position: 0.2 ; color: "#11000000" }
                }
                border.color: "darkgray"
                antialiasing: true
                radius: 4
            }
        }
    }

    Image {
        id: rightBtn
        source: "images/back.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 2
        anchors.right: parent.right
        anchors.rightMargin: 16

        MouseArea {
            hoverEnabled: true
            anchors.centerIn: parent
            width: 38
            height: 31
            anchors.verticalCenterOffset: -1
            enabled: activePageCount > 0
            onClicked: {
                rightBtnClicked()
                console.log("Bar Right Btn clicked")
            }
            Rectangle {
                anchors.fill: parent
                opacity: parent.pressed ? 1 : 0
                Behavior on opacity { NumberAnimation{ duration: 100 }}
                gradient: Gradient {
                    GradientStop { position: 0 ; color: "#22000000" }
                    GradientStop { position: 0.2 ; color: "#11000000" }
                }
                border.color: "darkgray"
                antialiasing: true
                radius: 4
            }
        }
    }
}
