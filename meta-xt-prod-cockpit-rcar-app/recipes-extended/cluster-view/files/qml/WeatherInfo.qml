import QtQuick 2.0

Item {
    id: weatherInfo
    x: 1756
    y: 40
    Image {
       id: cloud_img
       anchors.left: parent.left
       anchors.top: weatherInfo.top
       source: "../images/Cloudy.png"
       anchors.topMargin: 5
    }
    Text {
        id: tempInfo
        anchors.left: cloud_img.right
        anchors.top: weatherInfo.top
        anchors.leftMargin: 5
        font.pixelSize: 30
        color: "white"
        text: qsTr("23")
    }
    Image {
       id: temp_img
       anchors.left: tempInfo.right
       anchors.leftMargin: 5
       anchors.top: weatherInfo.top
       source: "../images/C.png"
    }
}
