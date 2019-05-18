import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    Rectangle   {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0; color: "#00000000"  }
            GradientStop { position: 0.2; color: "#00000000" }
            GradientStop { position: 0.5; color: "#4c4fc622"  }
            GradientStop { position: 0.8; color: "#00000000"  }
            GradientStop { position: 1.0; color: "#00000000" }
        }

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
                    text: qsTr("Smart vehicle control and monitoring system\n" +
                                "Target device: \"zaWRka\" (custom WR8 Flux smart vehicle)\n" +
                                "developed by department of Automatic Control Systems\n" +
                                "ETU \"LETI\" 2019\n" +
                                "App version: 0.2\n" +
                                "developed by Egor Sorokin\n" +
                                "ETU \"LETI\" 2019")
                    font.pointSize: 12
                    font.italic: true
                }
            }
        }
    }
}
