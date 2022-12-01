import QtQuick 2.0

Item {
    id: mainRange

    Image {
        id: rangeGauge
        source : "../images/Range_gauge.png"
        x: 1366
        y: 104
    }
    Image {
        id: range_img
        source : mainRange.rangeGauges[mainRange.currentRange].source
        x : mainRange.rangeGauges[mainRange.currentRange].x
        y : mainRange.rangeGauges[mainRange.currentRange].y
    }

    Item {
        id: rangeItem
        x: 1230
        y: 280
        width: 320
        height: rangeValueItem.height
        Text {
            id:rangeValueItem
            anchors.top: parent.top
            anchors.right: mi_img.left
            color: "white"
            font.pixelSize: 100
            text: Math.round(rangeValue).toString()
            anchors.rightMargin: 20
         }

        Image {
            id: mi_img
            source: "../images/mi.png"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
        }
    }

    Component.onCompleted: {
        currentRange = Qt.binding(function(){
            for (var i = 1; i < rangeGauges.length; i++) {
                if(rangeGauges[i-1].range < rangeValue && rangeGauges[i].range >= rangeValue)
                {
                    return i
                }
            }
            return 0
        }
        )
    }

    property var currentRange: 300
    property var rangeValue: 0
    property var rangeGauges : [
        {source: "../images//6mi.png", x: 1365, y: 538, range: 6},
        {source: "../images//12mi.png", x: 1365, y: 538, range: 12},
        {source: "../images//18mi.png", x: 1365, y: 538 , range: 18},
        {source: "../images//24mi.png", x: 1365, y: 538, range: 24},
        {source: "../images//30mi.png", x: 1365, y: 538, range: 30},
        {source: "../images//36mi.png", x: 1365, y: 538, range: 36},
        {source: "../images//42mi.png", x: 1365, y: 538, range: 42},
        {source: "../images//48mi.png", x: 1365, y: 538, range: 48},
        {source: "../images//48mi.png", x: 1365, y: 538, range: 54},
        {source: "../images//60mi.png", x: 1365, y: 538, range: 60},
        {source: "../images//66mi.png", x: 1365, y: 538, range: 66},
        {source: "../images//72mi.png", x: 1365, y: 538, range: 72},
        {source: "../images//78mi.png", x: 1365, y: 538, range: 78},
        {source: "../images//84mi.png", x: 1365, y: 538, range: 84},
        {source: "../images//90mi.png", x: 1365, y: 532, range: 90},
        {source: "../images//96mi.png", x: 1365, y: 523, range: 96},
        {source: "../images//102mi.png", x: 1365, y: 512, range: 102},
        {source: "../images//108mi.png", x: 1365, y: 503, range: 108},
        {source: "../images//114mi.png", x: 1365, y: 492, range: 114},
        {source: "../images//120mi.png", x: 1365, y: 483, range: 120},
        {source: "../images//126mi.png", x: 1365, y: 472, range: 126},
        {source: "../images//132mi.png", x: 1365, y: 463, range: 132},
        {source: "../images//138mi.png", x: 1365, y: 452, range: 138},
        {source: "../images//144mi.png", x: 1365, y: 443, range: 144},
        {source: "../images//150mi.png", x: 1365, y: 432, range: 150},
        {source: "../images//156mi.png", x: 1365, y: 423, range: 156},
        {source: "../images//162mi.png", x: 1365, y: 412, range: 162},
        {source: "../images//168mi.png", x: 1365, y: 403, range: 168},
        {source: "../images//174mi.png", x: 1365, y: 392, range: 174},
        {source: "../images//180mi.png", x: 1365, y: 383, range: 180},
        {source: "../images//186mi.png", x: 1365, y: 372, range: 168},
        {source: "../images//192mi.png", x: 1365, y: 363, range: 192},
        {source: "../images//198mi.png", x: 1365, y: 352, range: 198},
        {source: "../images//204mi.png", x: 1365, y: 343, range: 204},
        {source: "../images//210mi.png", x: 1365, y: 332, range: 210},
        {source: "../images//216mi.png", x: 1365, y: 323, range: 216},
        {source: "../images//222mi.png", x: 1365, y: 312, range: 222},
        {source: "../images//228mi.png", x: 1365, y: 303, range: 228},
        {source: "../images//234mi.png", x: 1365, y: 292, range: 234},
        {source: "../images//240mi.png", x: 1365, y: 283, range: 240},
        {source: "../images//246mi.png", x: 1365, y: 272, range: 246},
        {source: "../images//252mi.png", x: 1365, y: 263, range: 252},
        {source: "../images//258mi.png", x: 1365, y: 252, range: 258},
        {source: "../images//264mi.png", x: 1365, y: 243, range: 264},
        {source: "../images//270mi.png", x: 1365, y: 232, range: 270},
        {source: "../images//276mi.png", x: 1365, y: 223, range: 276},
        {source: "../images//282mi.png", x: 1365, y: 212, range: 282},
        {source: "../images//288mi.png", x: 1365, y: 203, range: 288},
        {source: "../images//294mi.png", x: 1365, y: 192, range: 294},
        {source: "../images//300mi.png", x: 1365, y: 183, range: 300},
    ]
}
