import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item {
    function showAddresses(addresses)   {
        connection_addresses_model.clear();
        for (var index in addresses)    {
            connection_addresses_model.append( { address: addresses[index] } );
        }
    }
    function connected()    {
        connection_connect_button.text = "Disconnect";
    }
    function disconnected() {
        connection_connect_button.text = "Connect";
    }
    function set(steering_p, steering_i, steering_d, steering_zero,
                 forward_p, forward_i, forward_d, forward_int,
                 backward_p, backward_i, backward_d, backward_int)  {

        settings_vehicle_steering_p.value = steering_p;
        settings_vehicle_steering_i.value = steering_i;
        settings_vehicle_steering_d.value = steering_d;
        settings_vehicle_steering_zero_slider.value = steering_zero;

        settings_vehicle_forward_p.value = forward_p;
        settings_vehicle_forward_i.value = forward_i;
        settings_vehicle_forward_d.value = forward_d;
        settings_vehicle_forward_int_slider.value = forward_int;

        settings_vehicle_backward_p.value = backward_p;
        settings_vehicle_backward_i.value = backward_i;
        settings_vehicle_backward_d.value = backward_d;
        settings_vehicle_backward_int_slider.value = backward_int;
    }

    Rectangle   {
        id: settings_container
        anchors.fill: parent

        RowLayout   {
            id: settings_row
            anchors.fill: parent
            anchors.margins: 20

            Rectangle   {
                id: commands_container
                Layout.columnSpan: 20
                Layout.rowSpan: 20
                Layout.fillHeight: true
                Layout.fillWidth: true
                anchors.margins: 10
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                color: "#f4f4f4"

                Image   {
                    id: commands_corner
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    source: "corner.png"
                }
                Label   {
                    id: commands_label
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 10
                    anchors.leftMargin: 30
                    text: qsTr("Commands")
                    font.pointSize: 14
                    font.bold: true
                }                
                Column  {
                    anchors.top: commands_label.bottom
                    anchors.left: parent.left
                    anchors.margins: 20
                    Row {
                        bottomPadding: 20
                        Label  {
                            id: commands_forward_text
                            text: qsTr("1. Move smart car forward for " + commands_forward_slider.value.toPrecision(3) + " centimeters.")
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
                        Button  {
                            id: commands_forwawrd_button
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
                            text: qsTr("2. Rotate smart vehicle's wheels for " + commands_wheels_slider.value.toPrecision(3) + " degrees.")
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
                        Button  {
                            id: commands_wheels_button
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

            ColumnLayout    {
                Layout.fillHeight: true
                Layout.fillWidth: true                

                Rectangle {
                    id: settings_vehicle
                    Layout.columnSpan: 20
                    Layout.rowSpan: 20
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    anchors.margins: 10
                    color: "#f4f4f4"
                    Image   {
                        id: settings_vehicle_corner
                        x: 0
                        y: 0
                        width: 30
                        height: 30
                        source: "corner.png"
                    }
                    Label   {
                        id: settings_vehicle_label
                        text: qsTr("Smart vehicle settings")
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.margins: 10
                        anchors.leftMargin: 30
                        font.pointSize: 14
                        font.bold: true
                    }

                    TabBar {
                        id: settings_vehicle_tabBar
                        anchors.margins: 10
                        anchors.top: settings_vehicle_label.bottom
                        anchors.left: parent.left
                        spacing: 10
                        background: Rectangle   {
                            opacity: 0
                        }

                        TabButton {
                            text: qsTr("Steering")
                            width: 100; height: 30
                            contentItem: Text {
                                text: parent.text
                                color: parent.checked ? "white" : "#4fc622"
                                font.pointSize: 12
                                horizontalAlignment: Text.AlignHCenter
                            }
                            background: Rectangle   {
                                color: parent.checked ? "#4fc622" : "#004fc622"
                                border.color: "#4fc622"
                                border.width: 1
                            }
                        }
                        TabButton {
                            text: qsTr("Forward")
                            width: 100; height: 30
                            contentItem: Text {
                                text: parent.text
                                color: parent.checked ? "white" : "#4fc622"
                                font.pointSize: 12
                                horizontalAlignment: Text.AlignHCenter
                            }
                            background: Rectangle   {
                                color: parent.checked ? "#4fc622" : "#004fc622"
                                border.color: "#4fc622"
                                border.width: 1
                            }
                        }
                        TabButton {
                            text: qsTr("Backward")
                            width: 100; height: 30
                            contentItem: Text {
                                text: parent.text
                                color: parent.checked ? "white" : "#4fc622"
                                font.pointSize: 12
                                horizontalAlignment: Text.AlignHCenter
                            }
                            background: Rectangle   {
                                color: parent.checked ? "#4fc622" : "#004fc622"
                                border.color: "#4fc622"
                                border.width: 1
                            }
                        }
                    }

                    StackLayout {
                        anchors.top: settings_vehicle_tabBar.bottom
                        anchors.left: parent.left
                        currentIndex: settings_vehicle_tabBar.currentIndex

                        Item {
                            id: settings_vehicle_steering
                            Column    {
                                anchors.fill: parent
                                padding: 10

                                Row {
                                    padding: 10
                                    spacing: 5
                                    Dial    {
                                        id: settings_vehicle_steering_p
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("P: ") + settings_vehicle_steering_p.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_steering_i
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("I: ") + settings_vehicle_steering_i.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_steering_d
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("D: ") + settings_vehicle_steering_d.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                }
                                Row {
                                    padding: 10
                                    Slider  {
                                        id: settings_vehicle_steering_zero_slider
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01

                                        background: Rectangle {
                                                x: parent.leftPadding
                                                y: parent.topPadding + parent.availableHeight / 2 - height / 2
                                                implicitWidth: 200
                                                implicitHeight: 4
                                                width: parent.availableWidth
                                                height: implicitHeight
                                                radius: 2
                                                color: "#bdbebf"

                                                Rectangle {
                                                    width: settings_vehicle_steering_zero_slider.visualPosition * parent.width
                                                    height: parent.height
                                                    color: "#4fc622"
                                                    radius: 2
                                                }
                                            }
                                    }
                                    Label   {
                                        id: settings_vehicle_steering_zero_label
                                        font.pointSize: 12
                                        text: qsTr("Servo zero state: \n") + settings_vehicle_steering_zero_slider.value.toPrecision(3)
                                    }

                                }
                            }
                        }
                        Item {
                            id: settings_vehicle_forward
                            Column    {
                                anchors.fill: parent
                                padding: 10

                                Row {
                                    padding: 10
                                    spacing: 5
                                    Dial    {
                                        id: settings_vehicle_forward_p
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("P: ") + settings_vehicle_forward_p.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_forward_i
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("I: ") + settings_vehicle_forward_i.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_forward_d
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("D: ") + settings_vehicle_forward_d.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                }
                                Row {
                                    padding: 10
                                    Slider  {
                                        id: settings_vehicle_forward_int_slider
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01

                                        background: Rectangle {
                                                x: parent.leftPadding
                                                y: parent.topPadding + parent.availableHeight / 2 - height / 2
                                                implicitWidth: 200
                                                implicitHeight: 4
                                                width: parent.availableWidth
                                                height: implicitHeight
                                                radius: 2
                                                color: "#bdbebf"

                                                Rectangle {
                                                    width: settings_vehicle_forward_int_slider.visualPosition * parent.width
                                                    height: parent.height
                                                    color: "#4fc622"
                                                    radius: 2
                                                }
                                            }
                                    }
                                    Label   {
                                        id: settings_vehicle_forward_int_label
                                        font.pointSize: 12
                                        text: qsTr("Integrator limit: \n") + settings_vehicle_forward_int_slider.value.toPrecision(3)
                                    }

                                }
                            }
                        }
                        Item {
                            id: settings_vehicle_backward
                            Column    {
                                anchors.fill: parent
                                padding: 10

                                Row {
                                    padding: 10
                                    spacing: 5
                                    Dial    {
                                        id: settings_vehicle_backward_p
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("P: ") + settings_vehicle_backward_p.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_backward_i
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("I: ") + settings_vehicle_backward_i.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_backward_d
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("D: ") + settings_vehicle_backward_d.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                }
                                Row {
                                    padding: 10
                                    Slider  {
                                        id: settings_vehicle_backward_int_slider
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01

                                        background: Rectangle {
                                                x: parent.leftPadding
                                                y: parent.topPadding + parent.availableHeight / 2 - height / 2
                                                implicitWidth: 200
                                                implicitHeight: 4
                                                width: parent.availableWidth
                                                height: implicitHeight
                                                radius: 2
                                                color: "#bdbebf"

                                                Rectangle {
                                                    width: settings_vehicle_backward_int_slider.visualPosition * parent.width
                                                    height: parent.height
                                                    color: "#4fc622"
                                                    radius: 2
                                                }
                                            }
                                    }
                                    Label   {
                                        id: settings_vehicle_backward_int_label
                                        font.pointSize: 12
                                        text: qsTr("Integrator limit: \n") + settings_vehicle_backward_int_slider.value.toPrecision(3)
                                    }

                                }
                            }
                        }
                    }

                    Row {
                        anchors.margins: 20
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        spacing: 10
                        Button  {
                            id: settings_vehicle_load
                            text: qsTr("Load")
                            onClicked:  {
                                adapter.slotUISettingsLoad(settings_vehicle_steering_p.value, settings_vehicle_steering_i.value,
                                                           settings_vehicle_steering_d.value, settings_vehicle_steering_zero_slider.value,
                                                           settings_vehicle_forward_p.value, settings_vehicle_forward_i.value,
                                                           settings_vehicle_forward_d.value, settings_vehicle_forward_int_slider.value,
                                                           settings_vehicle_backward_p.value, settings_vehicle_backward_i.value,
                                                           settings_vehicle_backward_d.value, settings_vehicle_backward_int_slider.value);
                            }

                        }
                        Button  {
                            id: settings_vehicle_upload
                            text: qsTr("Upload")
                            onClicked: {
                                adapter.slotUISettingsUpload();
                            }
                        }
                    }

                }
            }
        }
    }
}
