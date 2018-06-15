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
    property var dateTime
    property string classify
    property string kindFirst
    property string kindSecond
    property string goldFrom
    property double goldCount

    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinAddBill")
            {
                if (bar.rightStr == "+" &&
                        odvGoblinList.addBill(
                            dateTime.year, dateTime.month, dateTime.day,
                            dateTime.hour, dateTime.minute, dateTime.second, dateTime.customTime,
                            goldFrom, classify, kindFirst, kindSecond, goldCount,
                            monthSpinBox.value, firstMonthSpinBox.value, othersMonthSpinBox.value, content.text,
                            billSplitCheckBox.checkedState))
                {
                    console.log("addBil success")
                    content.text = ""
                    monthSpinBox.clear()
                    firstMonthSpinBox.clear()
                    othersMonthSpinBox.clear()
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

        RowSpinBox {
            id: monthSpinBox
            width: parent.width
            height: 60

            preText: "Month: "
        }

        RowSpinBox {
            id: firstMonthSpinBox
            width: parent.width
            height: 60

            boxDecimals: 2

            preText: "FirstMonth: "
        }

        RowSpinBox {
            id: othersMonthSpinBox
            width: parent.width
            height: 60

            boxDecimals: 2

            preText: "OthersMonth: "
        }

        Rectangle {
            width: parent.width
            height: 80
            border.color: "black"
            TextEdit {
                id: content
                anchors.fill: parent
            }
        }
        Row {
            width: parent.width
            height: 80

            Text {
                text: "billSplit: "
            }
            CheckBox {
                id: billSplitCheckBox

                checked: false
            }
        }
    }

}
