
import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1

Rectangle {
    id: mainRect
    width: 1000
    height: 700

    property alias currentIndex: root.currentIndex

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: root
            Layout.fillHeight: true
            Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 250
            focus: false
            orientation: ListView.Horizontal
            boundsBehavior: Flickable.StopAtBounds

            model: ObjectModel {
                TableTimeList {
                    id: listView
                    width: root.width
                    height: root.height
                }

                TableTimeAdd {
                    id: addView
                    width: root.width
                    height: root.height
                }
            }
        }
    }
}
