import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    Rectangle   {
        anchors.fill: parent

        Column    {
            anchors.fill: parent
            anchors.margins: 20
            Row {
                Label   {
                    text: qsTr("About app info")
                    font.pointSize: 12
                    font.bold: true
                }
            }

            Row {
                Label   {
                    text: qsTr("Target vehicle: WR8\nVersion: 0.2\nby Speedwagon\nОлег чисто girl")
                    font.pointSize: 12
                    font.italic: true
                }
            }
        }
    }
}
