
import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1
import ODVTime 1.0

Rectangle {
    id: mainRect

    ColumnLayout {
        anchors.fill: parent

        ODVTimeList { id: odvTimeList }

        ListView {
            id: rootTableTime
            Layout.fillHeight: true
            Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 250
            focus: false
            orientation: ListView.Horizontal
            boundsBehavior: Flickable.StopAtBounds

            onCurrentIndexChanged: {
                if (currentIndex == 0)
                {
                    // list
                    listView.updateCurList()
                    bar.leftStr = "<"
                    bar.middleStr = "List"
                    bar.rightStr = "-"
                    bar.barHandle = "handleTableTimeList"
                }
                else if (currentIndex == 1)
                {
                    // add
                    bar.leftStr = "<"
                    bar.middleStr = "Add"
                    bar.rightStr = "+"
                    bar.barHandle = "handleTableTimeAdd"
                }
            }

            model: ObjectModel {
                TableTimeList {
                    id: listView
                    height: rootTableTime.height
                    width: rootTableTime.width
                }

                TableTimeAdd {
                    id: addView
                    height: rootTableTime.height
                    width: rootTableTime.width
                }
            }
        }
    }
}
