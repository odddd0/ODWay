import QtQuick 2.9
import QtQuick.Controls 1.4
import ODVTime 1.0

Rectangle {
    property var treeObj: []
    property int treeObjCount: 0
    property var lastSelectIndex
    gradient: Gradient {
        GradientStop{ position: 0; color: "#E5F2F6";}
        GradientStop{ position: 1; color: "#B1DAE7";}
    }
    ODTreeModel { id: odvTimeSumModel }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableTimeSum")
            {
                rootTableTime.currentIndex = 1
            }
        }
    }

    function updateSum() {
        console.log("sum update")
        odvTimeSumModel.updateSum()
        bar.middleStr = odvTimeSumModel.daySum

        var obj = treeComponent.createObject(treeContain, {})
        for (var i = 0; i < treeObjCount; ++i)
        {
            treeObj.pop().destroy()
        }
        treeObjCount = 1
        treeObj.push(obj)
    }

    Rectangle {
        id: treeContain
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        color: "transparent"
    }

    Component {
        id: treeComponent
        TreeView {
            id: sumTreeView
            anchors.fill: parent
            model: odvTimeSumModel

            TableViewColumn {
                title: "Name"
                role: "name"
                resizable: true
            }

            TableViewColumn {
                title: "Time"
                role: "simplify"
                resizable: true
            }
            onClicked: {
                if (lastSelectIndex == index)
                {
                    if (sumTreeView.isExpanded(index))
                    {
                        sumTreeView.collapse(index)
                    }
                    else
                    {
                        sumTreeView.expand(index)
                    }
                }
                lastSelectIndex = index
                odvTimeSumModel.setSelectIndex(index)
            }
            onDoubleClicked: {
                if (sumTreeView.isExpanded(index))
                {
                    sumTreeView.collapse(index)
                }
                else
                {
                    sumTreeView.expand(index)
                }
                lastSelectIndex = index
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
                    if (odvTimeList.prevDay())
                    {
                        updateSum()
                    }
                }
                onPressAndHold: {
                    if (odvTimeList.firstDay())
                    {
                        updateSum()
                    }
                }
                Rectangle {
                    anchors.fill: parent
                    opacity: parent.pressed ? 1 : 0
                    Behavior on opacity { NumberAnimation{ duration: 100 }}
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: "#22000000" }
                        GradientStop { position: 0.2 ; color: "#11000000" }
                    }
                    border.color: "darkgray"
                    antialiasing: true
                    radius: 4
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
                    if (odvTimeList.nextDay())
                    {
                        updateSum()
                    }
                }
                onPressAndHold: {
                    if (odvTimeList.lastDay())
                    {
                        updateSum()
                    }
                }
                Rectangle {
                    anchors.fill: parent
                    opacity: parent.pressed ? 1 : 0
                    Behavior on opacity { NumberAnimation{ duration: 100 }}
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: "#22000000" }
                        GradientStop { position: 0.2 ; color: "#11000000" }
                    }
                    border.color: "darkgray"
                    antialiasing: true
                    radius: 4
                }
            }
        }
    }

}
