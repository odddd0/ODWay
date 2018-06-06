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

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableTimeList")
            {
                console.log("list right clicked")
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
                text: modelData
            }
        }
    }

    ListView {
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        id: tableTimeListView
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
            }
        }
    }
}
