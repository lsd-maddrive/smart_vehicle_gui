import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    property int map_width: 0
    property int map_height: 0
    property var cellList: undefined

    function setMap(w, h, newCellList)   {
        map_height = h;
        map_width = w;
        cellList = newCellList;
    }

    Rectangle   {
        id: container
        anchors.fill: parent
        anchors.margins: 20
        color: "#f4f4f4"

        Image   {
            id: log_corner
            width: 30
            height: 30
            source: "corner.png"
        }

        Label {
            id: log_label
            x: 30; y: -5
            text: qsTr("Map viewer")
            font.pointSize: 14
            font.bold: true
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 5
        }

        Column  {
            x: 0; y: 50
            Repeater    {
                id: column_repeater
                model: map_height
                delegate: Row {
                    id: row_container
                    Repeater    {
                        id: row_repeater
                        property int column_index: index
                        model: map_width
                        delegate: Rectangle   {
                             width: container.width / map_width
                             height: (container.height - 50) / map_height
                             color: (cellList[row_repeater.column_index * map_width + index] !== 1) ? "white" : "lightgray"
                             border.width: 1
                             border.color: "gray"
                        }
                    }
                }
            }
        }
    }
}
