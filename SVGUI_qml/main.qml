import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Smart Vehicle GUI (debug)")

    property string state: "DISCONNECTED"

    property string str_state_ready: qsTr("READY")
    property string str_state_run: qsTr("RUN")
    property string str_state_wait: qsTr("WAIT")
    property string str_state_fault: qsTr("FAULT")
    property string str_state_disconnected: qsTr("DISCONNECTED")

    signal signalTest()
    signal signalConnect()
    signal signalCommandForward()
    signal signalCommandWheels()

    Connections {
        target: adapter
        onSignalUILog:  {
            log_textArea.append(message)
        }

        onSignalUIConnected:    {
            console.log("Connected.");
            state = "CONNECTED";
            connection_window.visible = false;
            statusBar_label.text = str_state_ready;
        }

        onSignalUIDisconnected: {
            console.log("Disconnected");
            state = "DISCONNECTED";
            statusBar_label.text = str_state_disconnected;
        }

        onSignalUIConnectionError:  {
            console.log("Connection error");
            state = "DISCONNECTED";
            connection_error_modale.visible = true;
            statusBar_label.text = str_state_disconnected;
        }

        onSignalUIStatus:   {
            console.log("Incoming new status.");
            state = str;
            statusBar_label.text = str;
        }
        onSignalUIEncoderData:  {
            console.log("Incoming encoder data: " + encValue);
            values_list_model.setProperty(0, "value", encValue);
        }
        onSignalUIPotentiometerData:  {
            console.log("Incoming potentiometer data: " + potValue);
            values_list_model.setProperty(1, "value", potValue);
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: item.signalTest()
    }

    menuBar: MenuBar {
        id: menuBar
        MenuBarItem {
            id: menuBar_button_connection
            text: qsTr("Connection")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                connection_window.visible = true;
                console.log("connection action");
            }
        }
        MenuBarItem    {
            id: menuBar_button_commands
            text: qsTr("Commands")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                commands_window.visible = true;
                console.log("commands action");
            }
        }
        MenuBarItem    {
            id: menuBar_button_settings
            text: qsTr("Settings")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                settings_window.visible = true;
                console.log("settings action");
            }
        }
        MenuBarItem {
            id: menuBar_button_about
            text: qsTr("About")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                about_window.visible = true;
                console.log("about action");
            }
        }
    }

    header: ToolBar    {
        id: toolBar
        background: Rectangle   { color: "white"   }

        RowLayout   {
            Switch    {
                id: toolBar_log_switch
                text: qsTr("Show logs")
                checked: true
            }
            Switch    {
                id: toolBar_values_switch
                text: qsTr("Show values")
                checked: true
            }
        }
    }

    footer: Rectangle {
        id: statusBar
        gradient: Gradient {
            GradientStop { position: 0; color: "#00000000"  }
            GradientStop { position: 0.5; color: "#00000000" }
            GradientStop { position: 1; color: "#4c4fc622"  }
        }
        height: 25
        Label   {
            id: statusBar_label
            text: str_state_disconnected
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 2
            anchors.leftMargin: 10
        }
    }

    Rectangle   {
        id: content_container
        color: "#ffffff"
        anchors.fill: parent

        NumberAnimation on visible {
            duration: 1000
        }

        RowLayout {
            id: content_row
            anchors.rightMargin: 20
            anchors.leftMargin: 20
            anchors.bottomMargin: 20
            anchors.topMargin: 20
            anchors.fill: parent

            Rectangle   {
                id: log_container
                visible: toolBar_log_switch.checked
                width: 0
                height: 0
                color: "#f4f4f4"
                Layout.columnSpan: 20
                Layout.rowSpan: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                anchors.rightMargin: 20
                anchors.margins: 10
                //Layout.alignment: left

                Image   {
                    id: log_corner
                    width: 30
                    height: 30
                    source: "corner.png"
                }

                Label {
                    id: log_label
                    x: 30
                    y: -5
                    text: qsTr("LOG VIEWER")
                    font.weight: Font.DemiBold
                    font.pointSize: 14
                    font.capitalization: Font.SmallCaps
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    anchors.top: parent.top
                    anchors.topMargin: 5
                }

                ScrollView {
                    id: log_scrollView
                    anchors.fill: parent
                    padding: 20

                    TextArea {
                        id: log_textArea
                        x: 0
                        y: 30
                        width: 500
                        height: 500
                        text: qsTr("Application is ready.")
                        anchors.rightMargin: 20
                        anchors.leftMargin: 20
                        anchors.bottomMargin: 20
                        anchors.topMargin: 50
                        anchors.fill: parent
                        verticalAlignment: Text.AlignTop
                        placeholderText: qsTr("Logs...")
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        readOnly: true
                    }
                }
            }

            Rectangle   {
                id: values_container
                visible: toolBar_values_switch.checked
                Layout.columnSpan: 20
                Layout.rowSpan: 20
                Layout.fillHeight: true
                Layout.fillWidth: true
                //Layout.alignment: right
                anchors.margins: 10
                anchors.leftMargin: 20
                color: "#f4f4f4"

                Label {
                    id: values_label
                    text: qsTr("VALUES VIEWER")
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    font.weight: Font.DemiBold
                    font.pointSize: 14
                }

                Image   {
                    id: values_corner
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    source: "corner.png"
                }

                ListView    {
                    id: values_list
                    spacing: 5
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.bottomMargin: 20
                    anchors.topMargin: 40
                    anchors.fill: parent

                    model:  ListModel   {
                        id: values_list_model
                        ListElement {
                            name: "Encoder"
                            value: 0
                            measure: "smthng"
                        }
                        ListElement {
                            name: "Potentiometer"
                            value: 0
                            measure: "smthng"
                        }
                    }

                    delegate: Text {
                        font.pointSize: 12
                        text: name + ": " + value + " " + measure
                    }
                }
            }
        }
    }

    Window  {
        id: connection_window
        visible: false
        minimumWidth: 300
        minimumHeight: 250
        maximumWidth: 300
        maximumHeight: 250
        title: qsTr("Connection")
        modality: Qt.ApplicationModal
        
        Rectangle   {
            anchors.fill: parent
            anchors.margins: 10
            gradient: Gradient {
                GradientStop { position: 1; color: "#00000000"  }
                GradientStop { position: 0; color: "#4c4fc622"  }
            }

            Image   {
                id: connection_corner
                width: 30
                height: 30
                source: "corner.png"
            }
            
            Column  {
                Row {
                    Label   {
                        id: connection_label
                        text: qsTr("Connect to...")
                        font.bold: true
                        font.pointSize: 12
                        padding: 10
                    }
                }
                Row {
                    Label   {
                        id: connection_text
                        text: qsTr(" Enter an address and port of your\nWR8 Smart Vehicle to work with it.")
                        font.pointSize: 10
                        padding: 10
                    }
                }
                Row {
                    Label   {
                        id: connection_address_label
                        text: qsTr("Address")
                        font.pointSize: 10
                        width: 100
                        padding: 10
                    }
                    Rectangle   {
                        width: 150
                        height: connection_address_edit.height - 5
                        color: "white"
                        TextInput   {
                            id: connection_address_edit
                            width: 150
                            padding: 10
                            text: qsTr("127.0.0.1")
                            font.pointSize: 10
                        }
                    }
                }
                Row {
                    Label   {
                        id: connection_port_label
                        text: qsTr("Port")
                        font.pointSize: 10
                        width: 100
                        padding: 10
                    }
                    Rectangle   {
                        color: "white"
                        width: 150
                        height: connection_port_edit.height - 5
                        TextInput    {
                            id: connection_port_edit
                            width: 150
                            padding: 10
                            text: qsTr("80")
                            font.pointSize: 10
                        }
                    }
                }
                Row {
                    Button  {
                        id: connection_button
                        text: qsTr("Connect")
                        font.pointSize: 12
                        x: (connection_window.width - this.width) / 2
                        Layout.alignment: Layout.Center
                        onClicked: {
                            adapter.slotUIConnect(connection_address_edit.text, connection_port_edit.text);                            
                        }
                    }
                }
            }
        }

        Window  {
            id: connection_error_modale
            visible: false
            minimumWidth: 200
            minimumHeight: 100
            maximumWidth: 200
            maximumHeight: 100
            title: qsTr("Error")
            modality: Qt.ApplicationModal
            Image   {
                x: 20; y: 10
                width: 40; height: 40
                source: "error.png"
            }
            Label   {
                text: qsTr("Connection error")
                x: 70
                y: 20
            }
            Button  {
                id: connection_error_modale_ok
                text: qsTr("OK")
                x: 50
                y: 50
                onClicked: { connection_error_modale.close();    }
            }
        }

    }

    Window {
        id: commands_window
        visible: false
        width: 400
        height: 300
        title: qsTr("Commands")
        //modality: Qt.ApplicationModal

        Rectangle   {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0; color: "#00000000"  }
                GradientStop { position: 0.5; color: "#00000000" }
                GradientStop { position: 1; color: "#4c4fc622"  }
            }
            Column  {
                anchors.fill: parent
                padding: 20
                Row {
                    id: commands_forward
                    bottomPadding: 20
                    Button  {
                        id: commands_forwawrd_button
                        text: qsTr("Move forward for...")
                    }
                    Slider  {
                        id: commands_forward_slider
                        from: 10
                        to: 100
                        value: 50
                    }
                    Label  {
                        id: commands_forward_label
                        text: commands_forward_slider.value.toPrecision(3) + " sm"
                        font.pointSize: 14
                    }
                }
                Row {
                    id: commands_wheels
                    anchors.margins: 20
                    Button  {
                        id: commands_wheels_button
                        text: qsTr("Rotate wheels for...")
                    }
                    Slider  {
                        id: commands_wheels_slider
                        from: -50
                        to: 50
                        value: 0
                    }
                    Label  {
                        id: commands_wheels_label
                        text: commands_wheels_slider.value.toPrecision(3) + " grad"
                        font.pointSize: 14
                    }
                }
            }
        }
    }

    Window {
        id: settings_window
        visible: false
        width: 400
        height: 300
        title: qsTr("Settings")
        modality: Qt.ApplicationModal
    }

    Window {
        id: about_window
        visible: false
        width: 400
        height: 300
        title: qsTr("About")
        modality: Qt.ApplicationModal

        Label   {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("About app info")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }



}





















































/*##^## Designer {
    D{i:7;anchors_height:480;anchors_width:640}D{i:16;anchors_width:300}D{i:24;anchors_height:391;anchors_width:300;anchors_x:8;anchors_y:360}
D{i:12;anchors_width:300}
}
 ##^##*/
