import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtCharts 2.2

Item {
    property var speedSeries: charts_speed_series
    property var steeringSeries: charts_steering_series
    property var tempSeries: charts_temp_series
    property var tempSeriesFilter: charts_temp_series_filter

    function log(message)   {
        log_textArea.append(message);
        log_textArea.cursorPosition = log_textArea.length - 1;
    }
    function encoderSet(encValue)   {
        values_list_model.setProperty(0, "value", encValue);
    }
    function potentiometerSet(potValue) {
        values_list_model.setProperty(1, "value", potValue);
    }    
    function speedSet(speedValue)   {
        values_list_model.setProperty(2, "value", speedValue);
    }
    function tempSet(temp)  {
        values_list_model.setProperty(3, "value", temp);
    }
    function batterySet(number, batValue)   {
        values_list_model.setProperty(3 + number, "value", batValue);
    }

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
                                width: 0; height: 0
                                text: qsTr("Application is ready.")
                                padding: 10
                                topPadding: 40
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
                                    name: "Odometry"
                                    value: 0
                                    measure: "m"
                                }
                                ListElement {
                                    name: "Steering wheel"
                                    value: 0
                                    measure: "°"
                                }
                                ListElement {
                                    name: "Speed"
                                    value: 0
                                    measure: "mps"
                                }
                                ListElement {
                                    name: "Temperature"
                                    value: 0
                                    measure: "°С"
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
                                text: name + ": " + value.toPrecision(4) + " " + measure
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

                    RowLayout {
                        anchors.leftMargin: 40
                        anchors.topMargin: 10
                        anchors.top: parent.top
                        anchors.left: parent.left
                        Label {
                            id: charts_label
                            text: qsTr("Charts viewer")
                            font.bold: true
                            font.pointSize: 14
                            Layout.fillWidth: true
                        }
                        Button  {
                            id: charts_clear_button
                            height: 30
                            text: qsTr("Clear charts")
                            font.pointSize: 12
                            Layout.fillWidth: true
                            onClicked: {
                                adapter.slotUIClearCharts();
                            }
                        }
                    }

                    ScrollView   {
                        x: 0; y: charts_clear_button.height + 20
                        width: parent.width
                        height: parent.height - (charts_clear_button.height + 20)
                        contentWidth: charts_speed.width
                        contentHeight: charts_container.height * 1.5
                        clip: true
                        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                        ColumnLayout    {
                            width: charts_container.width
                            height: charts_container.height * 1.5
                            ChartView   {
                                id: charts_speed
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                antialiasing: true
                                backgroundRoundness: 10
                                theme: ChartView.ChartThemeQt
                                LineSeries {
                                    id: charts_speed_series
                                    name: "Vehicle speed"
                                    useOpenGL: true
                                    axisX: ValueAxis    {
                                        max: 60
                                        min: 0
                                    }
                                    axisY: ValueAxis    {
                                        min: -10
                                        max: 10
                                    }
                                }
                            }
                            ChartView   {
                                id: charts_steering
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                antialiasing: true
                                backgroundRoundness: 10
                                theme: ChartView.ChartThemeQt
                                LineSeries {
                                    id: charts_steering_series
                                    name: "Steering wheel rotating angle"
                                    useOpenGL: true
                                    axisX: ValueAxis    {
                                        max: 60
                                        min: 0
                                    }
                                    axisY: ValueAxis    {
                                        min: -10
                                        max: 10
                                    }
                                }
                            }
                            ChartView   {
                                id: charts_temp
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                antialiasing: true
                                backgroundRoundness: 10
                                theme: ChartView.ChartThemeQt
                                LineSeries {
                                    id: charts_temp_series
                                    name: "Temperature °C"
                                    useOpenGL: true
                                    style: Qt.DotLine
                                    axisX: ValueAxis    {
                                        max: 60
                                        min: 0
                                    }
                                    axisY: ValueAxis    {
                                        min: 0
                                        max: 100
                                    }
                                }
                                LineSeries  {
                                    id: charts_temp_series_filter
                                    name: "Filtered temperature °C"
                                    useOpenGL: true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
