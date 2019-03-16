import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    property int map_width: 0
    property int map_height: 0
    property var cellList: undefined
    property bool isVisible: false
    property int header_height: 50
    property double cell_width: container.width / map_width
    property double cell_height: (container.height - header_height) / map_height

    function setMap(w, h, newCellList)   {
        map_height = h;
        map_width = w;
        cellList = newCellList;
        isVisible = true;
        vehicle_img.visible = true;
    }
    function setPos(x, y, angle) {
        vehicle_img.x = x * cell_width - vehicle_img.width / 2;
        vehicle_img.y = y * cell_height - vehicle_img.height / 2 + header_height;
        vehicle_img.rotation = angle;
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

        Image   {
            id: no_map_img
            anchors.fill: parent
            source: "no_map.png"
            visible: !isVisible
        }

        Image {
            id: vehicle_img
            x: 0; y: 0
            visible: false
            width: cell_width / 3
            height: cell_height / 2
            source: "vehicle.png"
            z: 10
        }

        Column  {
            x: 0; y: header_height
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
                             width: cell_width
                             height: cell_height
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
