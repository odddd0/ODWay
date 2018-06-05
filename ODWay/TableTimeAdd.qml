import QtQuick 2.9

Rectangle {
    height: 640
    width: 480

    property bool init_

    Connections{
        target: bar
        onRightBtnClicked:{
            odvTimeList.addTime(dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second,
                                dateTime.customTime, classify.classText, kindFirst.classText, kindSecond.classText, content.text)
        }
    }

    Column {
        anchors.fill: parent
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
    }
}
