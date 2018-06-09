//====================================================================
//  DigitalPicker.qml
//  created 6.6.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9

Rectangle {
    property bool isOpen: false
    property bool noEcho: false
    property string theKey: "1243"
    property string numList

    height: parent.height
    width: parent.width
    color: "transparent"

    Component.onCompleted: {
        isOpen = theKey == ""
    }

    function addNum(num) {
        numList += num
        if (numList == theKey)
        {
            isOpen = true
        }
    }

    Column {
        anchors.fill: parent
        visible: !isOpen
        Row {
            width: parent.width
            height: parent.height / 3
            Rectangle {
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "7"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("7")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "8"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("8")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "9"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("9")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
        Row {
            width: parent.width
            height: parent.height / 3
            Rectangle {
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "4"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("4")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "5"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("5")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "6"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("6")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
        Row {
            width: parent.width
            height: parent.height / 3
            Rectangle {
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "1"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("1")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "2"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("2")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
                width: parent.width / 3
                height: parent.height
                color: "transparent"
                Text {
                    visible: !noEcho
                    anchors.centerIn: parent
                    text: "3"
                    font.pixelSize: Math.min(parent.height, parent.width)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        addNum("3")
                    }
                    Rectangle {
                        anchors.fill: parent
                        visible: !noEcho
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
}
