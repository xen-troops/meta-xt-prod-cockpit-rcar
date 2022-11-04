import QtQuick 2.0

Item {
    Text {
        id: timeInfo
        x: 40
        y: 40
        color: "white"
        font.pixelSize: 30
        text: {topInfo.timeUpdated;return Qt.formatTime(new Date(), "hh:mm ap")}
    }
}
