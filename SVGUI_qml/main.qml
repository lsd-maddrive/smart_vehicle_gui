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
        onSignalUIAddresses:    {
            console.log(addresses);
            for (var index in addresses)    {
                console.log(addresses[index]);
                connection_addresses_model.append( { address: addresses[index] } );
            }
        }
        onSignalUIConnected:    {
            console.log("Connected.");
            connection_state = "CONNECTED";
            statusBar_label.text = str_state_ready;
            connection_connect_button.text = "Disconnect";
        }

        onSignalUIDisconnected: {
            console.log("Disconnected");
            connection_state = "DISCONNECTED";
            statusBar_label.text = str_state_disconnected;
            connection_connect_button.text = "Connect";
        }

        onSignalUIConnectionError:  {
            console.log("Connection error");
            connection_state = "DISCONNECTED";
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
        onSignalUISettings: {
            console.log("Incoming new settings");
            settings_vehicle_p.value = p;
            settings_vehicle_i.value = i;
            settings_vehicle_d.value = d;
            settings_vehicle_zero_slider.value = zero;
        }
    }

/*
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
    }*/

    footer: Rectangle {
        id: statusBar
        gradient: Gradient {
            GradientStop { position: 0; color: "#00000000"  }
            GradientStop { position: 0.2; color: "#00000000" }
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

    SwipeView   {
        id: content_swipe
        anchors.fill: parent

        Item {
            id: content_item
            Rectangle   {
                id: content_container
                color: "#ffffff"
                anchors.fill: parent
                ColumnLayout    {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    anchors.fill: parent
                    RowLayout   {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
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
                            id: toolBar_charts_switch
                            text: qsTr("Show charts")
                            checked: true
                        }
                    }

                    RowLayout {
                        id: content_row
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.margins: 20

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
                                    text: qsTr("Log viewer")
                                    font.pointSize: 14
                                    font.bold: true
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
                                    text: qsTr("Values viewer")
                                    anchors.left: parent.left
                                    anchors.leftMargin: 40
                                    anchors.top: parent.top
                                    anchors.topMargin: 5
                                    font.bold: true
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
                                    anchors.margins: 20
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
                                            name: "Steering wheel"
                                            value: 0
                                            measure: "angle"
                                        }
                                        ListElement {
                                            name: "Motor battery"
                                            value: 0
                                            measure: "%"
                                        }
                                        ListElement {
                                            name: "Computer battery"
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
                                    text: qsTr("Charts viewer")
                                    Layout.alignment: Layout.TopLeft
                                    Layout.leftMargin: 40
                                    Layout.topMargin: 5
                                    font.bold: true
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
            }
        }

        Item {
            id: settings_item
            Rectangle   {
                id: settings_container
                anchors.fill: parent

                RowLayout   {
                    id: settings_row
                    anchors.fill: parent
                    anchors.margins: 20

                    Rectangle   {
                        id: connection_container
                        Layout.columnSpan: 20
                        Layout.rowSpan: 20
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        anchors.margins: 10
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20                        
                        color: "#f4f4f4"

                        Image   {
                            id: connection_corner
                            x: 0
                            y: 0
                            width: 30
                            height: 30
                            source: "corner.png"
                        }

                        Label   {
                            id: connection_label
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.margins: 10
                            anchors.leftMargin: 30
                            text: qsTr("Connection")
                            font.pointSize: 14
                            font.bold: true
                        }
                        Button  {
                            id: connection_search_button
                            anchors.top: connection_label.bottom
                            anchors.left: parent.left
                            anchors.margins: 10
                            width: parent.width - 40
                            text: qsTr("Search...")
                            font.pointSize: 12
                            onClicked: {
                                connection_addresses_model.clear();
                                adapter.slotUISearch();
                            }
                        }
                        Rectangle   {
                            id: connection_addresses_container
                            anchors.top: connection_search_button.bottom
                            anchors.bottom: connection_port_label.top
                            anchors.left: parent.left
                            anchors.margins: 20
                            ListView    {
                                id: connection_addresses_listView
                                anchors.fill: parent
                                spacing: 10
                                focus: true
                                addDisplaced: Transition {
                                    NumberAnimation { properties: "y"; from: 0; duration: 1000 }
                                }
                                model:  ListModel   {
                                    id: connection_addresses_model
                                }
                                highlight: Rectangle { color: "#4c4fc622"; z: 3 }
                                delegate: ItemDelegate {
                                    text: address
                                    font.pointSize: 12
                                    highlighted: ListView.isCurrentItem
                                    onClicked: {
                                        connection_addresses_listView.currentIndex = index;
                                    }
                                }
                            }
                        }
                        Label   {
                            id: connection_port_label
                            anchors.bottom: connection_connect_button.top
                            anchors.left: parent.left
                            anchors.margins: 20
                            text: qsTr("Port: ")
                            font.pointSize: 12
                            font.bold: true
                            width: 50
                        }
                        Rectangle {
                            id: connection_port_field
                            anchors.bottom: connection_connect_button.top
                            anchors.left: connection_port_label.right
                            anchors.margins: 10
                            width: 80
                            height: connection_port_label.height + 20
                            color: "white"
                            TextInput   {
                                id: connection_port_textInput
                                anchors.fill: parent
                                anchors.topMargin: 10
                                anchors.leftMargin: 10
                                text: qsTr("5556")
                                font.pointSize: 12
                            }
                        }
                        Button  {
                            id: connection_connect_button
                            width: parent.width - 40
                            anchors.margins: 20
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            text: qsTr("Connect")
                            font.pointSize: 12
                            enabled: connection_addresses_listView.currentItem
                            onClicked: {
                                if (connection_state == "DISCONNECTED") {
                                    var address = connection_addresses_model.get(connection_addresses_listView.currentIndex).address;
                                    var port = connection_port_textInput.text;
                                    adapter.slotUIConnect(address, port);
                                }   else    {
                                    adapter.slotUIDisconnect();
                                }
                            }
                        }
                    }

                    ColumnLayout    {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Rectangle   {
                            id: settings_ui
                            Layout.columnSpan: 20
                            Layout.rowSpan: 20
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            anchors.margins: 10
                            color: "#f4f4f4"
                            Image   {
                                id: settings_ui_corner
                                x: 0
                                y: 0
                                width: 30
                                height: 30
                                source: "corner.png"
                            }

                            Column    {
                                anchors.fill: parent
                                padding: 10
                                Label   {
                                    text: qsTr("Application settings")
                                    x: 30; y: -20
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
                            }
                        }

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

                            Column    {
                                anchors.fill: parent
                                padding: 10
                                Label   {
                                    text: qsTr("Smart vehicle settings")
                                    x: 30; y: -20
                                    font.pointSize: 14
                                    font.bold: true
                                }
                                Row {
                                    padding: 10
                                    spacing: 5
                                    Dial    {
                                        id: settings_vehicle_p
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("P: ") + settings_vehicle_p.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_i
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("I: ") + settings_vehicle_i.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                    Dial    {
                                        id: settings_vehicle_d
                                        width: 100; height: 100
                                        from: 0.1; to: 10
                                        value: 1
                                        stepSize: 0.01
                                        Label   {
                                            text: qsTr("D: ") + settings_vehicle_d.value.toPrecision(3)
                                            font.pointSize: 12
                                            x: 25; y: 40
                                        }
                                    }
                                }
                                Row {
                                    padding: 10
                                    Slider  {
                                        id: settings_vehicle_zero_slider
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
                                                    width: settings_vehicle_zero_slider.visualPosition * parent.width
                                                    height: parent.height
                                                    color: "#4fc622"
                                                    radius: 2
                                                }
                                            }
                                    }
                                    Label   {
                                        id: settings_vehicle_zero_label
                                        font.pointSize: 12
                                        text: qsTr("Servo zero state: \n") + settings_vehicle_zero_slider.value.toPrecision(3)
                                    }

                                }
                                Row {
                                    anchors.margins: 20
                                    spacing: 10
                                    Button  {
                                        id: settings_vehicle_load
                                        text: qsTr("Load")
                                        onClicked:  {
                                            adapter.slotUISettingsLoad(settings_vehicle_p.value, settings_vehicle_i.value,
                                                                       settings_vehicle_d.value, settings_vehicle_zero_slider.value);
                                        }

                                    }
                                    Button  {
                                        id: settings_vehicle_upload
                                        text: qsTr("Upoad")
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
        }
        Item {
            id: commands_item
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

        Item {
            id: about_item
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
    }
    PageIndicator {
        id: content_indicator
        count: content_swipe.count
        currentIndex: content_swipe.currentIndex
        anchors.bottom: content_swipe.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^## Designer {
    D{i:16;anchors_width:300}D{i:25;anchors_x:0;anchors_y:30}D{i:24;anchors_height:391;anchors_width:300;anchors_x:8;anchors_y:360}
D{i:7;anchors_height:480;anchors_width:640}D{i:12;anchors_width:300}
}
 ##^##*/
