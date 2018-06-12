//====================================================================
//  TableGoblinAdd.qml
//  created 6.12.18
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
            if (bar.barHandle == "handleTableGoblinAddBasic")
            {
                console.log("goblin add basic")
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
            id: goldFrom
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
    }

}
