import QtQuick 2.9

Rectangle {
    property bool init_

    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableTimeAdd")
            {
                if (bar.rightStr == "+" &&
                        odvTimeList.addTime(dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second,
                                            dateTime.customTime, classify.classText, kindFirst.classText, kindSecond.classText, content.text))
                {
                    content.text = ""
                    dateTime.dateEnable = false
                    rootTableTime.currentIndex = 1
                }
                else if (bar.rightStr == "Idle" && odvTimeList.fastIdle())
                {
                    rootTableTime.currentIndex = 1
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        spacing: 10
        Component.onCompleted: {
            console.log("1")
            init_ = true
        }

        DateTimePicker{
            width: parent.width
            id: dateTime
            Component.onCompleted: {
                console.log("11")
                init_ = false
            }
        }
        ClassifyPicker {
            width: parent.width
            height: 80
            id: classify
            classList: odvTimeList.classifyList
            onClassChanged: {
                console.log("2")
                if (!init_)
                {
                    odvTimeList.updateKindFirst(classify.classComboText)
                    kindFirst.classList = odvTimeList.kindFirstList
                    kindFirst.syncCombo()
                    odvTimeList.updateKindSecond(classify.classComboText, kindFirst.classComboText)
                    kindSecond.classList = odvTimeList.kindSecondList
                    kindSecond.syncCombo()
                }
            }
            Component.onCompleted: {
                console.log("5")
            }
        }
        ClassifyPicker {
            width: parent.width
            height: 80
            id: kindFirst
            classList: odvTimeList.kindFirstList
            onClassChanged: {
                console.log("3")
                if (!init_)
                {
                    odvTimeList.updateKindSecond(classify.classComboText, kindFirst.classComboText)
                    kindSecond.classList = odvTimeList.kindSecondList
                    kindSecond.syncCombo()
                }
            }
            Component.onCompleted: {
                console.log("4")
            }
        }
        ClassifyPicker {
            width: parent.width
            height: 80
            id: kindSecond
            classList: odvTimeList.kindSecondList
            Component.onCompleted: {
                console.log("6")
            }
        }
        Rectangle {
            width: parent.width
            height: 80
            border.color: "black"
            TextEdit {
                anchors.fill: parent
                id: content
            }
            Component.onCompleted: {
                console.log("7")
            }
        }

        Rectangle {
            width: parent.width
            height: 80
            color: "transparent"
            Rectangle {
                width: 100
                height: parent.height
                anchors.right: parent.right
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    width: 38
                    height: 31
                    anchors.verticalCenterOffset: -1
                    enabled: rightStr != ""
                    onPressAndHold: {
                        bar.rightStr = "Idle"
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
}
