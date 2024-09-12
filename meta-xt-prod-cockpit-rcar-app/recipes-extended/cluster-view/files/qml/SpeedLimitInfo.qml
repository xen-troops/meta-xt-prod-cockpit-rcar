import QtQuick 2.0

Item {
    id: speedLimitInfo
    x: 658
    y: 83
    Image {
       id: speed_limit_img
       anchors.left: speedLimitInfo.left
       anchors.top: speedLimitInfo.top
       source: "../images/Speed_limit_indicator_US.png"
    }
    /*Text {
        id: speedLimit
        anchors.centerIn: speed_limit_img
        color: "black"
        font.pixelSize: 30
        text: qsTr("50")
    }*/
}
