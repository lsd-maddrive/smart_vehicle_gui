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

    Rectangle   {
        id: connection_container
        anchors.fill: parent
        anchors.margins: 20
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
            text: qsTr("Network interfaces")
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
            anchors.bottom: connection_port_address.top
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

        RowLayout   {
            id: connection_port_address
            anchors.left: parent.left
            anchors.bottom: connection_connect_button.top
            anchors.margins: 20
            spacing: 20
            Label   {
                id: connection_address_label
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: qsTr("Address: ")
                font.pointSize: 12
                font.bold: true
                width: 70
            }
            Rectangle   {
                id: connection_address_field
                Layout.fillHeight: true
                Layout.fillWidth: true
                width: 120
                height: connection_address_label.height + 20
                color: "white"
                TextInput   {
                    id: connection_address_textInput
                    anchors.fill: parent
                    anchors.topMargin: 10
                    anchors.leftMargin: 10
                    text: connection_addresses_model.get(connection_addresses_listView.currentIndex).address
                    font.pointSize: 12
                }
            }
            Label   {
                id: connection_port_label
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: qsTr("Port: ")
                font.pointSize: 12
                font.bold: true
                width: 70
            }
            Rectangle {
                id: connection_port_field
                Layout.fillHeight: true
                Layout.fillWidth: true
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
}
