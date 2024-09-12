import QtQuick 2.0

Item {
    id: consumMain

    Image {
        id: consumeGauge
        source : "../images/Consumption_Gauge.png"
        x: 40
        y: 360
    }
    Image {
        id: consumeLevel
        source: "../images/Temperature_level.png"
        x: 160
        y: 506
    }

    Item {
        id: consumeLevelItem
        x: 40
        y: 567
        width: 200
        height: consumeValue.height
        Text {
            id:consumeValue
            anchors.top: parent.top
            color: "white"
            font.pixelSize: 30
            text: "4.4"//rangeValue.toString()
         }

        Image {
            id: kwh_img
            source: "../images/kWh.png"
            anchors.bottom: consumeValue.bottom
            anchors.left: consumeValue.right
            anchors.leftMargin: 10
        }
    }
}
