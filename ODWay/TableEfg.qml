//====================================================================
//  TableEfg.qml
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import ODVEfg 1.0
import "./ODBox" as ODBox

Rectangle {
    gradient: Gradient {
        GradientStop{ position: 0; color: "#EBEF70";}
        GradientStop{ position: 1; color: "#E0EF37";}
    }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = odvEfgList.getProgressStr()
        bar.rightStr = ""
        bar.barHandle = "handleTableEfg"
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableEfg" && bar.rightStr == "MARK")
            {
                if (odvEfgList.markIndex(tableEfgListView.currentIndex))
                {
                    bar.rightStr = ""
                    tableEfgListView.model = odvEfgList.getEfgStrList()
                }
            }
            bar.middleStr = odvEfgList.getProgressStr()
        }
    }

    ODVEfgList { id: odvEfgList }

    Component {
        id: tableEfgDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: 20
            color: "transparent"
            Text {
                id: wrapperText
                width: parent.width
                text: modelData
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    tableEfgListView.currentIndex = index
                    bar.rightStr = ""
                    wrapperText.color = "black"
                }
                onPressAndHold: {
                    tableEfgListView.currentIndex = index
                    wrapperText.color = "red"
                    bar.rightStr = "MARK"
                }
            }
            // indent the item if it is the current item
            states: [
                State {
                    name: "Current"
                    when: wrapper.ListView.isCurrentItem
                    PropertyChanges {
                        target: wrapperText
                        font.bold: true
                        font.underline: true
                        color: "black"
                    }
                },
                State {
                    name: "BaseDur"
                    PropertyChanges {
                        target: wrapperText
                        font.bold: false
                        font.underline: false
                        color: "black"
                    }
                }
            ]
        }
    }

    ListView {
        id: tableEfgListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        focus: false
        model: odvEfgList.getEfgStrList()
        delegate: tableEfgDelegate
    }

}

