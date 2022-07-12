import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Window 2.15

Window {
    id: window
    width: 800
    height: 600
    visible: true
    color: "black"

    Item {
        id: qt_logo
        width: 800
        height: 600
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10

        layer.enabled: true

        Rectangle {
            anchors.fill: parent
            color: "black"
            Image {
                id: car_img
                /*anchors.fill: parent*/
                anchors {
                  /*left: greenRect.left*/
                  bottom: parent.bottom
                }
                source: "Nav_car.png"
                x:317
                y:392
            }
            Text {
                x: 200
                y: 100
                anchors.bottom: car_img.top
                color: "white"
                font.pixelSize: 40
                text: qsTr("The Future is Written with Qt qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq")
            }
        }
    }
    
    MouseArea {
        id: mouseArea
        anchors.fill: qt_logo

        Text {
            id: clickme
            anchors.top: mouseArea.top
            anchors.horizontalCenter: mouseArea.horizontalCenter
            font.pixelSize: 17
            text: "Click me!"
            color: "white"

            SequentialAnimation on color {
                loops: Animation.Infinite
                ColorAnimation { duration: 400; from: "white"; to: "black" }
                ColorAnimation { duration: 400; from: "black"; to: "white" }
            }

            states: [
                State {
                    name: "flipped";
                    AnchorChanges {
                        target: clickme
                        anchors.top: undefined
                        anchors.bottom: mouseArea.bottom
                    }
                }
            ]
        }

        onClicked: {
            if (clickme.state == "flipped") {
                clickme.state = "";
                flip2.start();
            } else {
                clickme.state = "flipped";
                flip1.start();
            }
        }
    }
}
