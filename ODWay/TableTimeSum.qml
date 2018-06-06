import QtQuick 2.9
import QtQuick.Controls 1.4

Rectangle {
    anchors.topMargin: 5
    anchors.bottomMargin: 5
    anchors.leftMargin: 5
    anchors.rightMargin: 5

    gradient: Gradient {
        GradientStop{ position: 0; color: "#E5F2F6";}
        GradientStop{ position: 1; color: "#B1DAE7";}
    }

    TreeView {
        anchors.top: parent.top
        anchors.topMargin: 70
        model: tmpTreeModel
    }

    ListModel {
        id: tmpTreeModel

    }

}
