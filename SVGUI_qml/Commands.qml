import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    Rectangle   {
        anchors.fill: parent
        Column  {
            anchors.fill: parent
            padding: 20
            Row {
                bottomPadding: 20
                Label  {
                    id: commands_forward_text
                    text: qsTr("1. Move smart car forward for X centimeters.")
                    font.pointSize: 12
                }
            }

            Row {
                id: commands_forward
                bottomPadding: 20
                Slider  {
                    id: commands_forward_slider
                    from: 10
                    to: 100
                    value: 50
                }
                Label  {
                    id: commands_forward_label
                    text: commands_forward_slider.value.toPrecision(3) + " sm"
                    width: 80
                    font.pointSize: 14
                }
                Button  {
                    id: commands_forwawrd_button
                    x: commands_forward_label.x + commands_forward_label.width + 20
                    text: qsTr("Move")
                    enabled: (statusBar_label.text === "WAIT" || statusBar_label === "STOP")
                    onClicked: {
                        adapter.slotUICommandForward(commands_forward_slider.value);
                    }
                }
            }

            Row {
                bottomPadding: 20
                Label  {
                    id: commands_wheels_text
                    text: qsTr("2. Rotate smart vehicle's wheels for X degrees.")
                    font.pointSize: 12
                }
            }
            Row {
                id: commands_wheels
                anchors.margins: 20
                Slider  {
                    id: commands_wheels_slider
                    from: -50
                    to: 50
                    value: 0
                }
                Label  {
                    id: commands_wheels_label
                    text: commands_wheels_slider.value.toPrecision(3) + " grad"
                    width: 80
                    font.pointSize: 14
                }
                Button  {
                    id: commands_wheels_button
                    x: commands_wheels_label.x + commands_wheels_label.width + 20
                    text: qsTr("Rotate")
                    enabled: (statusBar_label.text === "WAIT" || statusBar_label === "STOP")
                    onClicked: {
                        adapter.slotUICommandWheels(commands_wheels_slider.value);
                    }
                }
            }

            Row {
                bottomPadding: 20
                Label  {
                    id: commands_ligths_text
                    text: qsTr("3. Flick smart vehicle's ligths 3 times.")
                    font.pointSize: 12
                }
            }
            Row {
                id: commands_lights
                anchors.margins: 20
                Button  {
                    id: commands_lights_button
                    text: qsTr("Flick")
                    enabled: (statusBar_label.text === "WAIT" || statusBar_label === "STOP")
                    onClicked: {
                        adapter.slotUICommandFlick();
                    }
                }
            }
        }
    }
}
