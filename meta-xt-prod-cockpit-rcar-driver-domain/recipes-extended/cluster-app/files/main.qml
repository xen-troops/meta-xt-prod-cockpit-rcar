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
        id: cluster_app
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
                anchors {
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
                text: qsTr("The Future is Written in Qt")
            }
        }
    }
}
