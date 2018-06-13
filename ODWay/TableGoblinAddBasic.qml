//====================================================================
//  TableGoblinAdd.qml
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4

Rectangle {
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
                if (bar.rightStr == "+" &&
                        odvGoblinList.addSimplePay(dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second,
                                                   dateTime.customTime, goldFrom.currentText, ckk.classify, ckk.kindFirst, ckk.kindSecond, count.value, content.text))
                {
                    rootTableGoblin.currentIndex = 0
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

        DateTimePicker{
            id: dateTime
            width: parent.width
        }
        CKKPicker {
            id: ckk
            width: parent.width
            height: 180
            ckkList: odvGoblinList.getCKK()
        }
        Row {
            width: parent.width
            height: 60
            spacing: 10

            ComboBox {
                id: goldFrom
                width: parent.width / 2 - 10
                height: parent.height
                model: odvGoblinList.getGoldFromList()
            }
            SpinBox {
                id: count
                width: parent.width / 2 - 10
                height: parent.height
                minimumValue: 0
                maximumValue: 2147483648
            }
        }

        Rectangle {
            width: parent.width
            height: 60
            border.color: "black"
            TextEdit {
                id: content
                anchors.fill: parent
            }
        }
    }

}
