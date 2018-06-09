//====================================================================
//  TableTimeAdd.qml
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

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
                    rootTableTime.currentIndex = 2
                }
                else if (bar.rightStr == "Idle" && odvTimeList.fastIdle())
                {
                    rootTableTime.currentIndex = 2
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
            init_ = true
        }

        DateTimePicker{
            width: parent.width
            id: dateTime
            Component.onCompleted: {
                init_ = false
            }
        }
        ClassifyPicker {
            width: parent.width
            height: 80
            id: classify
            classList: odvTimeList.classifyList
            onClassChanged: {
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
        }
        ClassifyPicker {
            width: parent.width
            height: 80
            id: kindFirst
            classList: odvTimeList.kindFirstList
            onClassChanged: {
                if (!init_)
                {
                    odvTimeList.updateKindSecond(classify.classComboText, kindFirst.classComboText)
                    kindSecond.classList = odvTimeList.kindSecondList
                    kindSecond.syncCombo()
                }
            }
        }
        ClassifyPicker {
            width: parent.width
            height: 80
            id: kindSecond
            classList: odvTimeList.kindSecondList
        }
        Rectangle {
            width: parent.width
            height: 80
            border.color: "black"
            TextEdit {
                anchors.fill: parent
                id: content
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
                    onDoubleClicked: {
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
