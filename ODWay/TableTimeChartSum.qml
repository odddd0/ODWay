//====================================================================
//  TableTimeChartSum.qml
//  created 6.11.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {

    function updateSum() {
        tableTimeChartSumListView.model = odvTimeList.getLastCKKSumStr()
    }

    Component {
        id: tableTimeChartSumDelegate
        Rectangle {
            id: wrapper
            width: parent.width
            height: 20
            color: "transparent"
            Text {
                id: wrapperText
                width: parent.width
                text: modelData
            }
            Component.onCompleted: {
                wrapperText.color = odvTimeList.getLastCKKSumStrColor(index, "black")
//                wrapperText.color = "green"
            }
        }
    }

    ListView {
        id: tableTimeChartSumListView
        anchors.fill: parent
        anchors.topMargin: 65 + 5
        anchors.bottomMargin: 55
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        focus: false
        model: odvTimeList.curList
        delegate: tableTimeChartSumDelegate
    }
}
