import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item {
    property bool isConnected: false
    property int control_sending_freq: 10

    Rectangle   {
        id: container
        anchors.fill: parent
        anchors.margins: 20
        color: "#f4f4f4"

        Image   {
            id: log_corner
            width: 30
            height: 30
            source: "corner.png"
        }

        Label {
            id: log_label
            x: 30; y: -5
            text: qsTr("Control panel")
            font.pointSize: 14
            font.bold: true
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 5
        }

        Switch  {
            id: control_switch
            anchors.centerIn: parent
            text: qsTr("Control")
            font.bold: true
            font.pointSize: 14
        }

        Label   {
            id: steering_control_label
            anchors.centerIn: steering_control
            text: steering_control.value.toPrecision(2)
            font.bold: true
            font.pointSize: 14
        }

        Dial    {
            property double moveInc: 0.1

            id: steering_control
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 30
            height: container.height / 2
            value: 0
            from: -1; to: 1
            enabled: control_switch.position

            background: Rectangle {
                x: steering_control.width / 2 - width / 2
                y: steering_control.height / 2 - height / 2
                width: Math.max(64, Math.min(steering_control.width, steering_control.height))
                height: width
                color: "transparent"
                radius: width / 2
                border.color: steering_control.pressed ? "#17a81a" : "#21be2b"
                opacity: steering_control.enabled ? 1 : 0.3
            }

            handle: Rectangle {
                id: handleItem
                x: steering_control.background.x + steering_control.background.width / 2 - width / 2
                y: steering_control.background.y + steering_control.background.height / 2 - height / 2
                width: 16
                height: 16
                color: steering_control.pressed ? "#17a81a" : "#21be2b"
                radius: 12
                antialiasing: true
                opacity: steering_control.enabled ? 1 : 0.3
                transform: [
                    Translate {
                        y: -Math.min(steering_control.background.width, steering_control.background.height) * 0.4 + handleItem.height / 2
                    },
                    Rotation {
                        angle: steering_control.angle
                        origin.x: handleItem.width / 2
                        origin.y: handleItem.height / 2
                    }
                ]
            }
        }

        Label   {
            id: engine_control_label
            text: engine_control.value.toPrecision(2)
            font.bold: true
            font.pointSize: 14
            anchors.margins: 30
            anchors.bottom: engine_control.top
            anchors.right: parent.right
        }

        Slider  {
            property double moveInc: 0.1

            id: engine_control
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 30
            height: container.height / 2
            value: 0
            from: -1; to: 1
            orientation: Qt.Vertical
            enabled: control_switch.position
            snapMode: "SnapOnRelease"

            background: Rectangle {
                x: engine_control.leftPadding
                y: engine_control.topPadding + engine_control.availableHeight / 2 - height / 2
                implicitWidth: 50
                implicitHeight: parent.height
                width: engine_control.availableWidth
                height: implicitHeight
                radius: 2
                color: "#bdbebf"
                opacity: engine_control.enabled ? 1.0 : 0.3

                Rectangle {
                    y: engine_control.visualPosition * parent.height
                    width: parent.width
                    height: parent.height - engine_control.visualPosition * parent.height
                    color: engine_control.pressed ? "#17a81a" : "#21be2b"
                    radius: 2
                }
            }
        }

        Timer   {
            id: control_timer
            repeat: true
            running: control_switch.position
            interval: 10
            onTriggered: {
                if (!engine_control.pressed)    {
                    if (engine_control.value > engine_control.moveInc)
                        engine_control.decrease();
                    if (engine_control.value < -engine_control.moveInc)
                        engine_control.increase();
                    if(Math.abs(engine_control.value) <= engine_control.moveInc)
                        engine_control.value = 0;
                }

                if (!steering_control.pressed)    {
                    if (steering_control.value > steering_control.moveInc)
                        steering_control.decrease();
                    if (steering_control.value < -steering_control.moveInc)
                        steering_control.increase();
                    if(Math.abs(steering_control.value) <= steering_control.moveInc)
                        steering_control.value = 0;
                }
            }
        }

        Timer   {
            id: send_timer
            repeat: true
            running: control_switch.position && isConnected
            interval: 1000 / control_sending_freq
            onTriggered: {
                adapter.slotUIControl(steering_control.value, engine_control.value);
            }
        }
    }
}
