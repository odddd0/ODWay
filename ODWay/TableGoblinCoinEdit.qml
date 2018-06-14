//====================================================================
//  TableGoblinCoinEdit.qml
//  created 6.14.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQuick.Controls 1.4
import ODVGoblin 1.0

Rectangle {
    gradient: Gradient {
        GradientStop{ position: 0; color: "#A1EF54";}
        GradientStop{ position: 1; color: "#89EF37";}
    }

    ODVGoblinList { id: vvGoblinList }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinCoinEdit" && bar.rightStr == "Save")
            {
                // save coin edit
                if (vvGoblinList.saveEditCoin(
                            revokeCheckBox.checkedState,
                            dateTime.year,
                            dateTime.month,
                            dateTime.day,
                            dateTime.hour,
                            dateTime.minute,
                            dateTime.second,
                            revokeSpinBox.value))
                {
                    bar.back()
                }
            }
        }
    }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = "Coin"
        bar.rightStr = "Save"
        bar.rightColor = "red"
        bar.barHandle = "handleTableGoblinCoinEdit"

        vvGoblinList.updateEditCoin()
        coinEditText.text = vvGoblinList.getEditCoinStrText()
        revokeCheckBox.checked = vvGoblinList.getEditCoinStrRevoke()
        revokeSpinBox.value = vvGoblinList.getEditCoinStrCountSecond()
        dateTime.isCustom = revokeCheckBox.checkedState
        dateTime.setYear = vvGoblinList.getEditCoinStrYear()
        dateTime.setMonth = vvGoblinList.getEditCoinStrMonth()
        dateTime.setDay = vvGoblinList.getEditCoinStrDay()
        dateTime.setHour = vvGoblinList.getEditCoinStrHour()
        dateTime.setMinute = vvGoblinList.getEditCoinStrMinute()
        dateTime.setSecond = vvGoblinList.getEditCoinStrSecond()
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        spacing: 10

        Text {
            id:  coinEditText
        }

        CheckBox {
            id: revokeCheckBox
            checked: false

            onCheckedChanged: {
                dateTime.boxVisiable = checked
                revokeSpinBox.boxVisiable = checked
                fastSecondButton.visible = checked
            }
        }

        DateTimePicker{
            id: dateTime
            width: parent.width

            boxVisiable: false
        }

        RowSpinBox {
            id: revokeSpinBox
            width: parent.width
            height: 60

            boxDecimals: 2

            preText: "Revoke: "
            boxVisiable: false
        }

        Rectangle {
            id: fastSecondButton
            width: parent.width
            height: 80
            color: "transparent"
            visible: false
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
                    onDoubleClicked: {
                        revokeSpinBox.value = vvGoblinList.getEditCoinStrCount()
                        console.log(vvGoblinList.getEditCoinStrCount())
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
