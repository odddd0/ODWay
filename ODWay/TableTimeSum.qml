//====================================================================
//  TableTimeSum.qml
//  created 6.6.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.9
import QtQuick.Controls 1.4
import ODVTime 1.0

Rectangle {
    property var treeObj: []
    property var lastSelectIndex
    property bool allSum: false
    gradient: Gradient {
        GradientStop{ position: 0; color: "#E5F2F6";}
        GradientStop{ position: 1; color: "#B1DAE7";}
    }
    ODTreeModel { id: odvTimeSumModel }

    Connections{
        target: bar
        onRightBtnClicked:{
            if (bar.barHandle == "handleTableTimeSum" && bar.rightStr == "x")
            {
                odvTimeSumModel.clearCKK()
                odvTimeList.clearCKKCur()
                bar.rightStr = "All"
            }
            else if (bar.barHandle == "handleTableTimeSum" && bar.rightStr == "All")
            {
                allSum = true
                bar.middleStr = "ALL"
                bar.rightStr = ""
            }
            updateSum()
        }
    }

    function updateSum() {
        odvTimeSumModel.updateSum(allSum)
        if (!allSum)
        {
            bar.middleStr = odvTimeSumModel.daySum
        }
        allSum = false

        // create and destroy Tree Object
        var obj = treeComponent.createObject(treeContain, {})
        for (var i = 0; i < treeObj.length; ++i)
        {
            treeObj.pop().destroy()
        }
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
        id: iiDelegate
        Rectangle {
            id: wrapper
            color: "transparent"
            Text {
                id: wrapperText
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                color: styleData.textColor
                elide: styleData.elideMode
                text: styleData.value
            }
            Component.onCompleted: {
                if (odvTimeSumModel.isSelectHighlight(model.classify, model.kindFirst, model.kindSecond))
                {
                    wrapperText.color = "#FFF300"
                    wrapper.color = "blue"
                }
            }
        }
    }

    Component {
        id: treeComponent
        TreeView {
            id: sumTreeView
            anchors.fill: parent
            model: odvTimeSumModel
            Component.onCompleted: {
                if (odvTimeSumModel.isFirstExpand())
                {
                    expand(odvTimeSumModel.getFirstExpand())
                }

                if (odvTimeSumModel.isSecondExpand())
                {
                    expand(odvTimeSumModel.getSecondExpand())
                }
            }

            TableViewColumn {
                title: "Name"
                role: "name"
                resizable: true
                delegate: iiDelegate
            }

            TableViewColumn {
                title: "Time"
                role: "simplify"
                resizable: true
                delegate: iiDelegate
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
                odvTimeList.setCKKCur(odvTimeSumModel.setSelectIndex(index))
                bar.rightStr = "x"
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
                bar.rightStr = "x"
            }
        }
    }

    // turn day Button
    Row {
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        // Prev day Button
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
        // Next day Button
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
