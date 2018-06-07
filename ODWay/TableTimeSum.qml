import QtQuick 2.9
import QtQuick.Controls 1.4
import ODVTime 1.0

Rectangle {
    anchors.topMargin: 5
    anchors.bottomMargin: 5
    anchors.leftMargin: 5
    anchors.rightMargin: 5

    gradient: Gradient {
        GradientStop{ position: 0; color: "#E5F2F6";}
        GradientStop{ position: 1; color: "#B1DAE7";}
    }

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
        odvTimeSumModel.updateSum()
        view.model = odvTimeSumModel
    }



    TreeView {
        id: view
        anchors.fill: parent
        anchors.topMargin: 70
        model: odvTimeSumModel

        TableViewColumn {
            title: "Name"
            role: "name"
            resizable: true
        }

        TableViewColumn {
            title: "Simplify"
            role: "simplify"
            resizable: true
        }
    }

}
