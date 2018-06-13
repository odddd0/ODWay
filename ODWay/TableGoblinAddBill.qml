//====================================================================
//  TableGoblinAdd.qml
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9

Rectangle {

    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinAddBill")
            {
                console.log("goblin add bill")
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
            width: parent.width
            id: dateTime
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
