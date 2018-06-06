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
        bar.middleStr = odvTimeList.GetRunningTime()
        bar.rightStr = "-"
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
            MouseArea { anchors.fill: parent; onClicked: tableTimeListView.currentIndex = index; }
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
                    tableTimeListView.model = odvTimeList.curList
                }
                onPressAndHold: {
                    odvTimeList.firstDay()
                    odvTimeList.updateList()
                    tableTimeListView.model = odvTimeList.curList
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
                    tableTimeListView.model = odvTimeList.curList
                }
                onPressAndHold: {
                    odvTimeList.lastDay()
                    odvTimeList.updateList()
                    tableTimeListView.model = odvTimeList.curList
                }
            }
        }
    }
}
