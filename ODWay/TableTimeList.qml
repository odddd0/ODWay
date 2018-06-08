import QtQuick 2.9

Rectangle {
    property bool selectMode: false
    property int index1: 0
    property int index2: 0
    property var lastWrapper
    gradient: Gradient {
        GradientStop{ position: 0; color: "#EBEF70";}
        GradientStop{ position: 1; color: "#E0EF37";}
    }

    Component.onCompleted: {
        // list
        updateCurList()
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
                if (bar.rightStr == "-")
                {
                    if (odvTimeList.delTime(tableTimeListView.currentIndex))
                    {
                        updateCurList()
                        bar.rightStr = ""
                    }
                }
                else if (bar.rightStr == "x")
                {
                    selectMode = false
                    bar.rightColor = "red"
                    bar.rightStr = ""
                    tableTimeListView.currentIndex = 0
                    lastWrapper.color = "transparent"
                }
            }
        }
    }

    function updateCurList() {
        odvTimeList.updateList()
        tableTimeListView.model = odvTimeList.curList
        selectMode = false
        bar.rightColor = "red"
        bar.rightStr = ""
        tableTimeListView.currentIndex = 0
    }

    function calDurTime() {
        if (selectMode && bar.rightStr == "x")
        {
            bar.middleStr = odvTimeList.calDurTime(index1, index2)
            console.log("1: ", index1)
            console.log("2: ", index2)
        }
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
                    if (selectMode)
                    {
                        if (wrapperText.text.charAt(2) == ':' &&
                                wrapperText.text.charAt(5) == '-' &&
                                wrapperText.text.charAt(8) == ':' &&
                                wrapperText.text.charAt(11) == '(' )
                        {
                            tableTimeListView.currentIndex = index
                            bar.rightStr = "x"
                        }
                        index2 = index
                        calDurTime()
                    }
                    else
                    {
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
                onDoubleClicked: {
                    if (!selectMode &&
                            wrapperText.text.charAt(2) == ':' &&
                            wrapperText.text.charAt(5) == '-' &&
                            wrapperText.text.charAt(8) == ':' &&
                            wrapperText.text.charAt(11) == '(' )
                    {
                        wrapper.color = "lightyellow"
                        selectMode = true
                        bar.rightStr = "x"
                        bar.rightColor = "blue"
                        index1 = index
                        lastWrapper = wrapper
                        calDurTime()
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
                    color: "black"
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
                    if (odvTimeList.prevDay())
                    {
                        updateCurList()
                    }
                }
                onPressAndHold: {
                    if (odvTimeList.firstDay())
                    {
                        updateCurList()
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
                        updateCurList()
                    }
                }
                onPressAndHold: {
                    if (odvTimeList.lastDay())
                    {
                        updateCurList()
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
