import QtQuick 2.9
import ODVTime 1.0

Rectangle {
    height: 640
    width: 480

    Component.onCompleted: {
        odvTimeList.updateList()
    }

    ODVTimeList {
        id: odvTimeList
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
}
