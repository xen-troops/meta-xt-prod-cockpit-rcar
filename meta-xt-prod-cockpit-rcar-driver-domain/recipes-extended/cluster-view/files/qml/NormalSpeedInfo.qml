import QtQuick 2.0

Item {
    id: mainSpeed

    Image {
        id: autoLight
        source : "../images/Speed_gauge.png"
        x: 40
        y: 114
    }
    Image {
        id: speed_img
        source : mainSpeed.speedGauges[mainSpeed.currentGauge].source
        x : 560 - mainSpeed.speedGauges[mainSpeed.currentGauge].width
        y : mainSpeed.speedGauges[mainSpeed.currentGauge].y
    }

    Item {
        id: speedItem
        x: 330
        y: 215
        width: 320
        height: speed.height
        Text {
            id:speed
            anchors.top: parent.top
            anchors.right: mph_img.left
            color: "white"
            font.pixelSize: 150
            text: Math.round(mainSpeed.speed*0.621371).toString()
            anchors.rightMargin: 20
         }

        Image {
            id: mph_img
            source: "../images/mph.png"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
        }
    }

    Component.onCompleted: {
        currentGauge = Qt.binding(function(){
            for (var i = 1; i < speedGauges.length; i++) {
                if(speedGauges[i-1].speed < Math.round(mainSpeed.speed*0.621371) && speedGauges[i].speed >= Math.round(mainSpeed.speed*0.621371))
                {
                    return i
                }
            }
            return 0
        }
        )
    }

    property var speed: 0
    property var currentGauge: 0

    property var speedGauges : [
        {source: "../images/3_mph.png", x: 487, y: 523, width: 73, speed: 3},
        {source: "../images/6_mph.png", x: 475, y: 523, width: 85, speed: 6},
        {source: "../images/9_mph.png", x: 462, y: 523, width: 98, speed: 9},
        {source: "../images/12_mph.png", x: 450, y: 523, width: 110, speed: 12},
        {source: "../images/15_mph.png", x: 437, y: 523, width: 123, speed: 15},
        {source: "../images/18_mph.png", x: 425, y: 523, width: 135, speed: 18},
        {source: "../images/21_mph.png", x: 412, y: 523, width: 148, speed: 21},
        {source: "../images/24_mph.png", x: 399, y: 523, width: 161, speed: 24},
        {source: "../images/27_mph.png", x: 386, y: 523, width: 174, speed: 27},
        {source: "../images/30_mph.png", x: 373, y: 523, width: 187, speed: 30},
        {source: "../images/33_mph.png", x: 361, y: 523, width: 199, speed: 33},
        {source: "../images/36_mph.png", x: 352, y: 523, width: 208, speed: 36},
        {source: "../images/39_mph.png", x: 345, y: 523, width: 215, speed: 39},
        {source: "../images/42_mph.png", x: 337, y: 523, width: 223, speed: 42},
        {source: "../images/45_mph.png", x: 329, y: 523, width: 231, speed: 45},
        {source: "../images/48_mph.png", x: 321, y: 513, width: 239, speed: 48},
        {source: "../images/51_mph.png", x: 314, y: 503, width: 246, speed: 51},
        {source: "../images/54_mph.png", x: 306, y: 492, width: 254, speed: 54},
        {source: "../images/57_mph.png", x: 299, y: 482, width: 261, speed: 57},
        {source: "../images/60_mph.png", x: 291, y: 472, width: 269, speed: 60},
        {source: "../images/63_mph.png", x: 284, y: 462, width: 276, speed: 63},
        {source: "../images/66_mph.png", x: 276, y: 452, width: 284, speed: 66},
        {source: "../images/69_mph.png", x: 268, y: 442, width: 292, speed: 69},
        {source: "../images/72_mph.png", x: 261, y: 432, width: 299, speed: 72},
        {source: "../images/75_mph.png", x: 255, y: 422, width: 305, speed: 75},
        {source: "../images/78_mph.png", x: 246, y: 412, width: 314, speed: 78},
        {source: "../images/81_mph.png", x: 246, y: 410, width: 314, speed: 81},
        {source: "../images/84_mph.png", x: 231, y: 392, width: 329, speed: 84},
        {source: "../images/87_mph.png", x: 224, y: 382, width: 336, speed: 87},
        {source: "../images/90_mph.png", x: 216, y: 372, width: 344, speed: 90},
        {source: "../images/93_mph.png", x: 209, y: 362, width: 351, speed: 93},
        {source: "../images/96_mph.png", x: 201, y: 352, width: 359, speed: 96},
        {source: "../images/99_mph.png", x: 193, y: 342, width: 367, speed: 99},
        {source: "../images/102_mph.png", x: 186, y: 332, width: 374, speed: 102},
        {source: "../images/105_mph.png", x: 178, y: 322, width: 382, speed: 105},
        {source: "../images/108_mph.png", x: 171, y: 312, width: 389, speed: 108},
        {source: "../images/111_mph.png", x: 163, y: 302, width: 397, speed: 111},
        {source: "../images/114_mph.png", x: 156, y: 292, width: 404, speed: 114},
        {source: "../images/117_mph.png", x: 148, y: 282, width: 412, speed: 117},
        {source: "../images/120_mph.png", x: 141, y: 272, width: 419, speed: 120},
        {source: "../images/123_mph.png", x: 133, y: 262, width: 427, speed: 123},
        {source: "../images/126_mph.png", x: 126, y: 252, width: 434, speed: 126},
        {source: "../images/129_mph.png", x: 118, y: 242, width: 442, speed: 129},
        {source: "../images/132_mph.png", x: 111, y: 232, width: 449, speed: 132},
        {source: "../images/135_mph.png", x: 103, y: 222, width: 457, speed: 135},
        {source: "../images/138_mph.png", x: 96, y: 213, width: 464, speed: 138},
        {source: "../images/141_mph.png", x: 88, y: 203, width: 472, speed: 141},
        {source: "../images/144_mph.png", x: 81, y: 193, width: 479, speed: 144},
        {source: "../images/147_mph.png", x: 73, y: 183, width: 487, speed: 147},
        {source: "../images/150_mph.png", x: 66, y: 173, width: 494, speed: 150},
    ]
}
