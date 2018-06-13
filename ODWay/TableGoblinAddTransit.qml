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

    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinAddTransit")
            {
                console.log("goblin add transit")
                if (bar.rightStr == "+" &&
                        odvGoblinList.addNormalTransit(dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second,
                                                   dateTime.customTime, goldFrom.currentText, goldTo.currentText, count.value, content.text))
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

        ComboBox {
            id: transitType
            width: parent.width
            height: 60
            model: ["Normal"]
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

            ComboBox {
                id: goldTo
                width: parent.width / 2 - 10
                height: parent.height
                model: odvGoblinList.getGoldFromList()
            }
        }
        SpinBox {
            id: count
            width: parent.width
            height: 60
            decimals: 2
            minimumValue: 0
            maximumValue: 2147483648
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
