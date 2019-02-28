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

    property real data_visualisation_frequency: settings_item.data_visualisation_frequency

    property real charts_encoder_current: 0
    property real charts_potentiometer_current: 0
    property real charts_time: 0
    property int charts_max_time: 60

    Connections {
        target: adapter
        onSignalUILog:  {
            content_item.log(message)
        }                
        onSignalUIAddresses:    {
            console.log(addresses);
            settings_item.showAddresses(addresses);
        }
        onSignalUIConnected:    {
            console.log("Connected.");
            connection_state = "CONNECTED";
            statusBar_label.text = str_state_ready;
            settings_item.connected();
        }

        onSignalUIDisconnected: {
            console.log("Disconnected");
            connection_state = "DISCONNECTED";
            statusBar_label.text = str_state_disconnected;
            settings_item.disconnected();
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
        onSignalUISettings: {
            console.log("Incoming new settings");
            settings_item.newSet(p, i, d, zero);
        }
        onSignalUIUpdateData:   {
            charts_encoder_current = encValue;
            content_item.encoderSet(encValue);
            charts_potentiometer_current = potValue;
            content_item.potentiometerSet(potValue);
            content_item.batterySet(1, firstBatteryValue);
            content_item.batterySet(2, secondBatteryValue);
        }
    }

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

        Content {
            id: content_item
            data_visualization_frequency: data_visualisation_frequency
        }

        Settings {
            id: settings_item
        }

        Commands {
            id: commands_item
        }

        About {
            id: about_item
        }
    }
    PageIndicator {
        id: content_indicator
        count: content_swipe.count
        currentIndex: content_swipe.currentIndex
        anchors.bottom: content_swipe.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Component.onCompleted: {
        adapter.slotUISetSerieses(content_item.encoderSeries, content_item.potentiometerSeries);
    }
}

/*##^## Designer {
    D{i:16;anchors_width:300}D{i:25;anchors_x:0;anchors_y:30}D{i:24;anchors_height:391;anchors_width:300;anchors_x:8;anchors_y:360}
D{i:7;anchors_height:480;anchors_width:640}D{i:12;anchors_width:300}
}
 ##^##*/
