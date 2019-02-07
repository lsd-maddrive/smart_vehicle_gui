import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtCharts 2.2

ApplicationWindow {
    id: mainWindow
    visible: true
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("Smart Vehicle GUI (debug)")  

    property string connection_state: qsTr("DISCONNECTED")

    property string str_state_ready: qsTr("READY")
    property string str_state_run: qsTr("RUN")
    property string str_state_wait: qsTr("WAIT")
    property string str_state_fault: qsTr("FAULT")
    property string str_state_disconnected: qsTr("DISCONNECTED")

    property real charts_encoder_current: 0
    property real charts_potentiometer_current: 0
    property real charts_time: 0
    property int charts_max_time: 60

    Connections {
        target: adapter
        onSignalUILog:  {
            log_textArea.append(message);
            log_textArea.cursorPosition = log_textArea.length - 1;
        }

        onSignalUIConnected:    {
            console.log("Connected.");
            connection_state = "CONNECTED";
            connection_window.visible = false;
            statusBar_label.text = str_state_ready;
            connection_button.text = "Disconnect";
        }

        onSignalUIDisconnected: {
            console.log("Disconnected");
            connection_state = "DISCONNECTED";
            statusBar_label.text = str_state_disconnected;
            connection_button.text = "Connect";
        }

        onSignalUIConnectionError:  {
            console.log("Connection error");
            connection_state = "DISCONNECTED";
            //connection_error_modale.visible = true;
            statusBar_label.text = str_state_disconnected;
        }

        onSignalUIStatus:   {
            console.log("Incoming new status.");
            statusBar_label.text = str;
        }
        onSignalUIEncoderData:  {
            console.log("Incoming encoder data: " + encValue);
            values_list_model.setProperty(0, "value", encValue);
            charts_encoder_current = encValue;
        }
        onSignalUIPotentiometerData:  {
            console.log("Incoming potentiometer data: " + potValue);
            values_list_model.setProperty(1, "value", potValue);
            charts_potentiometer_current = potValue;
        }
        onSignalUIBatteryData:  {
            console.log("Incoming " + number + " battery data: " + value);
            values_list_model.setProperty(1 + number, "value", value);
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {}
    }

    menuBar: MenuBar {
        id: menuBar
        MenuBarItem {
            id: menuBar_button_connection
            text: qsTr("Connection")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                connection_window.visible = true;
            }
        }
        MenuBarItem    {
            id: menuBar_button_commands
            text: qsTr("Commands")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                commands_window.visible = true;
            }
        }
        MenuBarItem    {
            id: menuBar_button_settings
            text: qsTr("Settings")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                settings_window.visible = true;
            }
        }
        MenuBarItem {
            id: menuBar_button_about
            text: qsTr("About")
            display: AbstractButton.TextBesideIcon
            onTriggered: {
                about_window.visible = true;
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
            Switch    {
                id: toolBar_connection_switch
                text: qsTr("Show connection")
                checked: false
            }
            Switch    {
                id: toolBar_charts_switch
                text: qsTr("Show charts")
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

            ColumnLayout    {
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: toolBar_log_switch.checked || toolBar_values_switch.checked
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
                    ScrollView  {
                        contentHeight: 0
                        contentWidth: 0
                        anchors.fill: parent
                        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                        TextArea {
                            id: log_textArea
                            x: 0
                            y: 0
                            width: 0
                            height: 0
                            text: qsTr("Application is ready.")
                            leftPadding: 10
                            padding: 10
                            rightPadding: 10
                            bottomPadding: 10
                            topPadding: 40
                            anchors.rightMargin: 0
                            anchors.leftMargin: 0
                            anchors.bottomMargin: 0
                            anchors.topMargin: 0
                            clip: false
                            visible: true
                            anchors.fill: parent
                            font.pointSize: 11
                            renderType: Text.QtRendering
                            verticalAlignment: Text.AlignTop
                            placeholderText: qsTr("Logs...")
                            wrapMode: Text.WordWrap
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
                    anchors.margins: 10
                    anchors.leftMargin: 20
                    anchors.rightMargin: 20
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

                    Column  {
                        anchors.fill: parent


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
                            ListElement {
                                name: "Battery 1"
                                value: 0
                                measure: "%"
                            }
                            ListElement {
                                name: "Battery 2"
                                value: 0
                                measure: "%"
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

            Rectangle   {
                id: connection_container
                visible: toolBar_connection_switch.checked
                Layout.columnSpan: 20
                Layout.rowSpan: 20
                Layout.fillHeight: true
                Layout.fillWidth: true
                anchors.margins: 10
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                color: "#f4f4f4"
                Column  {
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
                                validator: RegExpValidator  { regExp: /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/ }
                                font.pointSize: 10
                                focus: true
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
                                maximumLength: 5
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
                                if (connection_state == "DISCONNECTED")   {
                                    adapter.slotUIConnect(connection_address_edit.text, connection_port_edit.text);
                                }   else    {
                                    adapter.slotUIDisconnect();
                                }
                            }
                        }
                    }
                    }
                }

            Rectangle   {
                id: charts_container
                visible: toolBar_charts_switch.checked
                Layout.columnSpan: 20
                Layout.rowSpan: 20
                Layout.fillHeight: true
                Layout.fillWidth: true
                anchors.margins: 10
                anchors.leftMargin: 20
                color: "#f4f4f4"

                Image   {
                    id: charts_corner
                    x: 0
                    y: 0
                    width: 30
                    height: 30
                    source: "corner.png"
                }

                ColumnLayout    {
                    anchors.fill: parent
                    Label {
                        id: charts_label
                        text: qsTr("CHARTS VIEWER")
                        Layout.alignment: Layout.TopLeft
                        Layout.leftMargin: 40
                        Layout.topMargin: 5
                        font.weight: Font.DemiBold
                        font.pointSize: 14
                    }
                    ChartView   {
                        id: charts_encoder
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        antialiasing: true
                        backgroundRoundness: 10
                        theme: ChartView.ChartThemeQt
                        LineSeries {
                            id: charts_encoder_series
                            name: "Encoder"
                            axisX: ValueAxis    {
                                 id: charts_encoder_time_axis
                                 max: charts_max_time
                                 min: 0
                                 tickCount: charts_max_time / 10 + 1
                            }
                            axisY: ValueAxis    {
                                id: charts_encoder_axis
                                min: -10
                                max: 10
                            }
                        }
                    }
                    ChartView   {
                        id: charts_potentiometer
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        antialiasing: true
                        backgroundRoundness: 10
                        theme: ChartView.ChartThemeQt
                        LineSeries {
                            id: charts_potentiometer_series
                            name: "Potentiometer"
                            axisX: ValueAxis    {
                                id: charts_potentiometer_time_axis
                                max: charts_max_time
                                min: 0
                                tickCount: charts_max_time / 10 + 1
                            }
                            axisY: ValueAxis    {
                                id: charts_potentiometer_axis
                                min: -10
                                max: 10
                            }
                        }
                    }

                    Timer   {
                        interval: 1000 / charts_frequency_spinBox.value
                        running: connection_state == "CONNECTED"
                        repeat: true
                        onTriggered: {
                            charts_encoder_series.insert(0, charts_time, charts_encoder_current);
                            charts_potentiometer_series.insert(0, charts_time, charts_potentiometer_current);

                            if (charts_encoder_current >= charts_encoder_axis.max)
                                charts_encoder_axis.max = charts_encoder_current + 1;
                            if (charts_encoder_current <= charts_encoder_axis.min)
                                charts_encoder_axis.min = charts_encoder_current - 1;
                            if (charts_potentiometer_current >= charts_potentiometer_axis.max)
                                charts_potentiometer_axis.max = charts_potentiometer_current + 1;
                            if (charts_potentiometer_current <= charts_potentiometer_axis.min)
                                charts_potentiometer_axis.min = charts_potentiometer_current - 1;

                            charts_time += 1 / charts_frequency_spinBox.value;
                            if (charts_time > charts_max_time)    {
                                charts_encoder_series.clear();
                                charts_potentiometer_series.clear();
                                charts_time = 0;
                            }
                        }
                    }
                }
            }
        }
    }
/*
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
                        text: qsTr(" Enter an address and port of yours\nWR8 Smart Vehicle to work with it.")
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
                            validator: RegExpValidator  { regExp: /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/ }
                            font.pointSize: 10
                            focus: true
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
                            maximumLength: 5
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
                            if (connection_state == "DISCONNECTED")   {
                                adapter.slotUIConnect(connection_address_edit.text, connection_port_edit.text);
                            }   else    {
                                adapter.slotUIDisconnect();
                            }
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
            Label   { text: qsTr("Connection error"); x: 70; y: 20  }
            Button  {
                id: connection_error_modale_ok
                text: qsTr("OK")
                x: 50; y: 50
                onClicked: { connection_error_modale.close();    }
            }
        }
    }
    */

    Window {
        id: commands_window
        visible: false
        minimumWidth: 500
        minimumHeight: 300
        maximumWidth: 500
        maximumHeight: 300
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

    Window {
        id: settings_window
        visible: false
        minimumWidth: 400
        minimumHeight: 300
        title: qsTr("Settings")
        //modality: Qt.ApplicationModal

        SwipeView {
            id: settings_swipe
            anchors.fill: parent
            background: Rectangle   {
                gradient: Gradient {
                    GradientStop { position: 0; color: "#00000000"  }
                    GradientStop { position: 0.5; color: "#00000000" }
                    GradientStop { position: 1; color: "#4c4fc622"  }
                }
            }

            Item {
                id: settings_ui
                Column    {
                    anchors.fill: parent
                    anchors.margins: 20
                    Label   {
                        text: qsTr("Application settings")
                        font.pointSize: 14
                        font.bold: true
                    }
                    Row {
                        padding: 10
                        Label   {
                            text: qsTr("Data visualization frequency: ")
                            font.pointSize: 12
                        }
                        SpinBox {
                            id: charts_frequency_spinBox
                            stepSize: 1
                            value: 1
                            from: 1
                            to: 30
                        }
                    }
                    Row {
                        padding: 10
                        Label   {
                            text: qsTr("Another parameter...")
                            font.pointSize: 12
                        }
                    }
                }
            }
            Item {
                id: settings_vehicle
                Column    {
                    anchors.fill: parent
                    anchors.margins: 20
                    Label   {
                        text: qsTr("Smart vehicle settings")
                        font.pointSize: 14
                        font.bold: true
                    }
                    Row {
                        padding: 10
                        Label   {
                            text: qsTr("paremeters...")
                            font.pointSize: 12
                        }
                    }
                }
            }
        }
        PageIndicator {
            id: indicator
            count: settings_swipe.count
            currentIndex: settings_swipe.currentIndex
            anchors.bottom: settings_swipe.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Window {
        id: about_window
        visible: false
        minimumWidth: 250
        minimumHeight: 200
        maximumWidth: 250
        maximumHeight: 200
        title: qsTr("About")
        modality: Qt.ApplicationModal

        Rectangle   {
            gradient: Gradient {
                GradientStop { position: 0; color: "#00000000"  }
                GradientStop { position: 0.5; color: "#00000000" }
                GradientStop { position: 1; color: "#4c4fc622"  }
            }
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
                        text: qsTr("Version: 0.1\nby Speedwagon")
                        font.pointSize: 12
                        font.italic: true
                    }
                }
            }
        }
    }
}


/*##^## Designer {
    D{i:16;anchors_width:300}D{i:25;anchors_x:0;anchors_y:30}D{i:24;anchors_height:391;anchors_width:300;anchors_x:8;anchors_y:360}
D{i:7;anchors_height:480;anchors_width:640}D{i:12;anchors_width:300}
}
 ##^##*/
