import QtQuick 2.9

Rectangle {
    anchors.topMargin: 5
    anchors.bottomMargin: 5
    anchors.leftMargin: 5
    anchors.rightMargin: 5
    gradient: Gradient {
        GradientStop{ position: 0; color: "#EBEF70";}
        GradientStop{ position: 1; color: "#E0EF37";}
    }

    Component.onCompleted: {
        // list
        listView.updateCurList()
        bar.leftStr = "<"
        bar.middleStr = odvTimeList.runningTimeStr
        bar.rightStr = ""
        bar.barHandle = "handleTableTimeList"
    }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableTimeList")
            {
                console.log("list right clicked")
                if (odvTimeList.delTime(tableTimeListView.currentIndex))
                {
                    updateCurList()
                    bar.rightStr = ""
                    console.log("delete complete")
                }
            }
        }
    }

    function updateCurList() {
        tableTimeListView.model = odvTimeList.curList
    }

    Component {
        id: tableTimeListViewDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: 20
            color: "transparent"
            Text {
                id: wrapperText
                text: modelData
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    tableTimeListView.currentIndex = index
                    if (wrapperText.text.charAt(2) == ':' &&
                            wrapperText.text.charAt(5) == '-' &&
                            wrapperText.text.charAt(8) == ':' &&
                            wrapperText.text.charAt(11) == '(' )
                    {
                        bar.rightStr = "-"
                    }
                    else
                    {
                        bar.rightStr = ""
                    }
                }
            }
            // indent the item if it is the current item
            states: State {
                name: "Current"
                when: wrapper.ListView.isCurrentItem
                PropertyChanges {
                    target: wrapperText
                    font.bold: true
                    font.underline: true
                }
            }
        }
    }

    ListView {
        id: tableTimeListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        focus: false
        model: odvTimeList.curList
        delegate: tableTimeListViewDelegate
    }

    Row {
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        Rectangle {
            width: parent.width / 2
            height: parent.height
            anchors.left: parent.left
            color: "lightgreen"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("clicked table time list left")
                    odvTimeList.prevDay()
                    odvTimeList.updateList()
                    updateCurList()
                }
                onPressAndHold: {
                    odvTimeList.firstDay()
                    odvTimeList.updateList()
                    updateCurList()
                }
            }
        }
        Rectangle {
            width: parent.width / 2
            height: parent.height
            anchors.right: parent.right
            color: "lightblue"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("clicked table time list right")
                    odvTimeList.nextDay()
                    odvTimeList.updateList()
                    updateCurList()
                }
                onPressAndHold: {
                    odvTimeList.lastDay()
                    odvTimeList.updateList()
                    updateCurList()
                }
            }
        }
    }
}
