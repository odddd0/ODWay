import QtQuick 2.9

Rectangle {
    height: 640
    width: 480

    Component.onCompleted: {
        odvTimeList.updateList()
    }

    function updateCurList() {
        console.log("update")
        tableTimeListView.model = odvTimeList.curList
    }

    ListView {
        anchors.fill: parent
        id: tableTimeListView
        focus: false
        model: odvTimeList.curList
        delegate: tableTimeListViewDelegate
    }
    Component {
        id: tableTimeListViewDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: 20
            Text {
                id: contactInfo
                text: modelData
            }
        }
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
