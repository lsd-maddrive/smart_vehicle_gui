import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item {
    property int control_sending_freq: settings_ui_control_sending_freq.value

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

        settings_vehicle_common_p.text = steering_p;
        settings_vehicle_common_i.text = steering_i;
        settings_vehicle_common_d.text = steering_d;
        settings_vehicle_common_zero.value = steering_zero;

        settings_vehicle_forward_p.value = forward_p;
        settings_vehicle_forward_i.value = forward_i;
        settings_vehicle_forward_d.value = forward_d;
        settings_vehicle_forward_intLimit.value = forward_int;

        settings_vehicle_backward_p.value = backward_p;
        settings_vehicle_backward_i.value = backward_i;
        settings_vehicle_backward_d.value = backward_d;
        settings_vehicle_backward_intLimit.value = backward_int;
    }

    Rectangle   {
        id: settings_container
        anchors.fill: parent

        RowLayout   {
            id: settings_row
            anchors.fill: parent
            anchors.margins: 20

            Rectangle   {
                id: settings_ui_container
                Layout.columnSpan: 20
                Layout.rowSpan: 20
                Layout.fillHeight: true
                Layout.fillWidth: true
                anchors.margins: 10
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                color: "#f4f4f4"

                Image   {
                    id: settings_ui_corner
                    x: 0; y: 0
                    width: 30
                    height: 30
                    source: "corner.png"
                }
                Label   {
                    id: settings_ui_label
                    text: qsTr("Smart vehicle settings")
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 10
                    anchors.leftMargin: 30
                    font.pointSize: 14
                    font.bold: true
                }

                ColumnLayout    {
                    y: 50
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Row {
                        Layout.margins: 20
                        spacing: 20
                        Label   {
                            text: qsTr("Sending frequency")
                            font.bold: true
                            font.pointSize: 12
                        }
                        SpinBox {
                            id: settings_ui_control_sending_freq
                            value: 100
                            from: 10; to: 1000
                            stepSize: 10
                            editable: true
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
                        x: 0; y: 0
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
                            text: qsTr("Common")
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
                            id: settings_vehicle_common
                            anchors.margins: 20

                            Grid  {
                                padding: 20
                                columns: 2
                                columnSpacing: 10
                                rowSpacing: 10
                                Label   {
                                    text: "P"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_common_p
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "P coefficient..."
                                }
                                Label   {
                                    text: "I"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_common_i
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "I coefficient..."
                                }
                                Label   {
                                    text: "D"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_common_d
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "D coefficient..."
                                }
                                Label   {
                                    text: "Zero"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_common_zero
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "Servo zero state..."
                                }
                            }
                        }
                        Item {
                            id: settings_vehicle_forward
                            Grid  {
                                padding: 20
                                columns: 2
                                columnSpacing: 10
                                rowSpacing: 10
                                Label   {
                                    text: "P"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_forward_p
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "P coefficient..."
                                }
                                Label   {
                                    text: "I"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_forward_i
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "I coefficient..."
                                }
                                Label   {
                                    text: "D"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_forward_d
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "D coefficient..."
                                }
                                Label   {
                                    text: "Int. limit"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_forward_intLimit
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "Intergator limit..."
                                }
                            }
                        }
                        Item {
                            id: settings_vehicle_backward
                            Grid  {
                                padding: 20
                                columns: 2
                                columnSpacing: 10
                                rowSpacing: 10
                                Label   {
                                    text: "P"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_backward_p
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "P coefficient..."
                                }
                                Label   {
                                    text: "I"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_backward_i
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "I coefficient..."
                                }
                                Label   {
                                    text: "D"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_backward_d
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "D coefficient..."
                                }
                                Label   {
                                    text: "Int. limit"
                                    font.pointSize: 12
                                }
                                TextField   {
                                    id: settings_vehicle_backward_intLimit
                                    validator: DoubleValidator{ bottom: 0; top: 100 }
                                    text: "1.0"
                                    placeholderText: "Intergator limit..."
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
                                adapter.slotUISettingsLoad(settings_vehicle_common_p.value, settings_vehicle_common_i.value,
                                                           settings_vehicle_common_d.value, settings_vehicle_common_zero.value,
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
