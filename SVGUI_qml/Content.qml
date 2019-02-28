import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtCharts 2.2

Item {
    property double data_visualization_frequency: 1
    property var encoderSeries: charts_encoder_series
    property var potentiometerSeries: charts_potentiometer_series
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
    function batterySet(number, batValue)   {
        values_list_model.setProperty(1 + number, "value", batValue);
    }
    function updateCharts() {

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
                                useOpenGL: true
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
                                useOpenGL: true
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
                            interval: 1000 / data_visualization_frequency
                            //running: connection_state == "CONNECTED"
                            running: false
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

                                charts_time += 1 / data_visualization_frequency;
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
