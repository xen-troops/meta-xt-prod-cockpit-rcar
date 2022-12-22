import QtQuick 2.0

Item {
    id: odoInfo
    x:1755
    y: 653
    Text {
        id: odo
        anchors.left: odoInfo.left
        color: "white"
        font.pixelSize: 30
        text: qsTr("3378 MI")
    }
}
