
import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.1
import ODVTime 1.0

Rectangle {
    id: mainRect

    ColumnLayout {
        anchors.fill: parent

        ODVTimeList { id: odvTimeList }
        ODTreeModel { id: odvTimeSumModel }

        Item {
            Timer {
                interval: 500; running: true; repeat: true
                onTriggered: {
                    if (bar.barHandle == "handleTableTimeAdd" ||
                            bar.barHandle == "handleTableTimeList")
                    {
                        bar.middleStr = odvTimeList.runningTimeStr
                    }
                }
            }
        }

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
            currentIndex: 1

            onCurrentIndexChanged: {
                if (currentIndex == 0)
                {
                    // add
                    bar.leftStr = "<"
                    bar.middleStr = odvTimeSumModel.daySum
                    bar.rightStr = ">"
                    bar.rightColor = "black"
                    bar.barHandle = "handleTableTimeSum"
//                    timeSum.updateSum()
                }
                else if (currentIndex == 1)
                {
                    // list
                    listView.updateCurList()
                    bar.leftStr = "<"
                    bar.middleStr = odvTimeList.runningTimeStr
                    bar.rightStr = ""
                    bar.rightColor = "red"
                    bar.barHandle = "handleTableTimeList"
                }
                else if (currentIndex == 2)
                {
                    // add
                    bar.leftStr = "<"
                    bar.middleStr = odvTimeList.runningTimeStr
                    bar.rightStr = "+"
                    bar.rightColor = "red"
                    bar.barHandle = "handleTableTimeAdd"
                }
            }

            model: ObjectModel {
                TableTimeSum {
                    id: timeSum
                    height: rootTableTime.height
                    width: rootTableTime.width
                }

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
