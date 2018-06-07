import QtQuick 2.0
//import QtGraphicalEffects 1.0

Rectangle {
    property string barHandle
    property string leftStr
    property string middleStr
    property string rightStr
    property string rightColor: "red"

    id: bar
    height: activePageCount > 0 ? 65 : 0
    width: parent.width
    visible: height > 0

    Behavior on height {
        NumberAnimation {
            duration: 100
        }
    }

    gradient: Gradient {
        GradientStop { position: 0 ; color: "#FFFFFFFF" }
        GradientStop { position: 1 ; color: "#000000FF" }
    }

    signal rightBtnClicked

    Rectangle {
        height: 1
        color: "#AAA"
        anchors.bottom: bar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        height: parent.height - 30
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        color: "transparent"
        Rectangle {
            id: leftRect
            height: parent.height
            width: 80
            anchors.left: parent.left
            color: "transparent"

            Text {
                anchors.centerIn: parent
                text: leftStr
                font.bold: true
                font.pixelSize: 22
            }

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                width: 38
                height: 31
                anchors.verticalCenterOffset: -1
                enabled: leftStr != ""
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
        Rectangle {
            id: middleRect
            height: parent.height
            anchors.left: leftRect.right
            anchors.right: rightRect.left
            color: "transparent"

            Text {
                id: middleLable
                anchors.centerIn: parent
                text: middleStr
                font.pixelSize: 30
            }
        }
        Rectangle {
            id: rightRect
            height: parent.height
            width: 80
            anchors.right: parent.right
            color: "transparent"

            Text {
                anchors.centerIn: parent
                text: rightStr
                font.pixelSize: 22
                font.bold: true
                color: rightColor
            }

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                width: 38
                height: 31
                anchors.verticalCenterOffset: -1
                enabled: rightStr != ""
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
}
