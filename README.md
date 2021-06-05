# smart_vehicle_gui

### Bachelor's degree work.
This project is intended to control and monitor the driverless smart vehicle «zaWRka» built on the base of the RC car model «WR8 Flux». The main tool is the cross-platform application with GUI. It may be connected with the car via WiFi for the data exchange. It uses a custom exchange protocol based on the TCP. Following vehicle's parameters are monitored in real-time:
 - wheel odometry
 - steering wheel angle
 - speed
 - temperature of the on-board computer
 - motor battery charge
 - on-board computer battery charge

Some of these parameters may be shown in the form of chart lines. Also, manual control of the steering wheel and the engine is available.

Initially, there was an idea to add the two following features: a visual representation of the surrounding area (in the form of a 2D map) and sending the single one-time control commands to the smart vehicle. These features were implemented but were not properly tested.

For the moment, the project consists of the following parts:
 - cross-platform GUI for the car control and monitoring (SVGUI_qml)
 - server code intended for the on-board computer of the vehicle (common/SVServer)
 - test application intended for the car mocking (SVServerGUI and SVServer_console)

The project is based on the **Qt** framework. Version 4 or higher is required.
