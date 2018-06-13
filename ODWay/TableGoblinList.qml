//====================================================================
//  TableGoblinList.qml
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9

Rectangle {
    // 0: default; 1: durMode; 2: deleteMode
    property bool selectMode: false
    property int index1: 0
    property int index2: 0
    property var lastWrapper
    gradient: Gradient {
        GradientStop{ position: 0; color: "#EBEF70";}
        GradientStop{ position: 1; color: "#E0EF37";}
    }

    Component.onCompleted: {
        bar.leftStr = "<"
        bar.middleStr = "List"
        bar.rightStr = ""
        bar.rightColor = "black"
        bar.barHandle = "handleTableGoblinList"
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableGoblinList" && bar.rightStr == "Add")
            {
                // open TableGoblinAddGnome
                bar.rightStr = ""
                bar.deepIn()
                ll.showExample("TableGoblinAddGnome.qml")
            }
        }
    }

    function updateCurList() {
        tableGoblinListView.model = ""
        tableGoblinListView.model = odvGoblinList.getGnomeList()
    }

    Component {
        id: tableGoblinListViewDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: 60
            color: "transparent"
            Text {
                id: wrapperText
                width: parent.width
                font.pixelSize: 20
                text: modelData
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    tableGoblinListView.currentIndex = index
                    if (wrapperText.text != "Add")
                    {
                        bar.rightStr = ""
                    }
                }
                onDoubleClicked: {
                    if (wrapperText.text == "Add")
                    {
                        bar.rightStr = "Add"
                    }
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
                        color: "black"
                    }
                },
                State {
                    name: "Normal"
                    PropertyChanges {
                        target: wrapperText
                        font.bold: false
                        color: "black"
                    }
                }
            ]
        }
    }


    ListView {
        id: tableGoblinListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        focus: false
        model: odvGoblinList.getGnomeList()
        delegate: tableGoblinListViewDelegate
    }

    ListModel{
        id: aaa
        ListElement{name:"Add"}
    }
}

