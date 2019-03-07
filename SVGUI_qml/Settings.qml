import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1

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
    function newSet(p, i, d, zero)  {
        settings_vehicle_p.value = p;
        settings_vehicle_i.value = i;
        settings_vehicle_d.value = d;
        settings_vehicle_zero_slider.value = zero;
    }
    property double data_visualisation_frequency: charts_frequency_spinBox.value

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
                    id: connection_address_label
                    anchors.left: parent.left
                    anchors.bottom: connection_port_label.top
                    anchors.margins: 20
                    text: qsTr("Address: ")
                    font.pointSize: 12
                    font.bold: true
                    width: 70
                }
                Rectangle   {
                    id: connection_address_field
                    anchors.left: connection_address_label.right
                    anchors.bottom: connection_port_label.top
                    anchors.margins: 10
                    width: 120
                    height: connection_address_label.height + 20
                    color: "white"
                    TextInput   {
                        id: connection_address_textInput
                        anchors.fill: parent
                        anchors.topMargin: 10
                        anchors.leftMargin: 10
                        text: connection_addresses_model.get(connection_addresses_listView.currentIndex).address;
                        font.pointSize: 12
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
                    width: 70
                }
                Rectangle {
                    id: connection_port_field
                    anchors.bottom: connection_connect_button.top
                    anchors.left: connection_port_label.right
                    anchors.margins: 10
                    width: 120
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
                            var address = connection_address_textInput.text;
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
