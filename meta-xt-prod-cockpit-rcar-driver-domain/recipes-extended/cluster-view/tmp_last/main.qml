import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Window 2.15

Window {
    id: window
    width: 800
    height: 360
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint

    Item {
        id: topInfo
        width: 800
        height: 360
        anchors.fill: parent
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            Image {
                id: cluster_img
                anchors {
                  bottom: parent.bottom
                }
                source: "cluster-bkg.png"
                x:0
                y:0
            }
        }
    }
    Text {
        x: 0
        y: 0
        //anchors.bottom: car_img.top
        color: "blue"
        font.pixelSize: 80
        text: qsTr("Any info displayed Qt 12345678901234567890")
     } 
/*
    Item {
        id: cluster_app
        width: 1920
        height: 720
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 0

        layer.enabled: true

        Rectangle {
            anchors.fill: parent
            color: "black"
            Image {
                id: cluster_img
                anchors {
                  bottom: parent.bottom
                }
                source: "cluster-bkg.png"
                x:0
                y:0
            }
        }
    }*/
}
