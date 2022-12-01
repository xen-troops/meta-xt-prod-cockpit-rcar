import QtQuick 2.0

Item {
    id: mainSportSpeed
    x: 660
    y: 70
    width: 599
    height: 576
    Text {
        id:speed
        anchors.centerIn: mainSportSpeed
        color: "white"
        font.pixelSize: 150
        text: Math.round(mainSportSpeed.speed*0.621371).toString()
     }
    Text {
        id: mph
        anchors.top: speed.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: "gray"
        font.pixelSize: 30
        text: "mph"
        anchors.topMargin: 20
     }

    Image {
        id: speed_gauge_img
        source : mainSportSpeed.speedGaugeImages[mainSportSpeed.speedGaugeIndex].source
        anchors.centerIn: mainSportSpeed
     }

    property var speed: 0

    property var speedGaugeImages : [
        {source: "../images/5_MPH.png", speed: 5},
        {source: "../images/10_MPH.png", speed: 10},
        {source: "../images/15_MPH.png", speed: 15},
        {source: "../images/20_MPH.png", speed: 20},
        {source: "../images/25_MPH.png", speed: 25},
        {source: "../images/30_MPH.png", speed: 30},
        {source: "../images/35_MPH.png", speed: 35},
        {source: "../images/40_MPH.png", speed: 40},
        {source: "../images/45_MPH.png", speed: 45},
        {source: "../images/50_MPH.png", speed: 50},
        {source: "../images/55_MPH.png", speed: 55},
        {source: "../images/60_MPH.png", speed: 60},
        {source: "../images/65_MPH.png", speed: 65},
        {source: "../images/70_MPH.png", speed: 70},
        {source: "../images/75_MPH.png", speed: 75},
        {source: "../images/80_MPH.png", speed: 80},
        {source: "../images/85_MPH.png", speed: 85},
        {source: "../images/90_MPH.png", speed: 90},
        {source: "../images/95_MPH.png", speed: 95},
        {source: "../images/100_MPH.png", speed: 100},
        {source: "../images/105_MPH.png", speed: 105},
        {source: "../images/110_MPH.png", speed: 110},
        {source: "../images/115_MPH.png", speed: 115},
        {source: "../images/120_MPH.png", speed: 120},
        {source: "../images/125_MPH.png", speed: 125},
        {source: "../images/130_MPH.png", speed: 130},
        {source: "../images/135_MPH.png", speed: 135},
        {source: "../images/140_MPH.png", speed: 140},
        {source: "../images/145_MPH.png", speed: 145},
        {source: "../images/150_MPH.png", speed: 150}
    ]

    property var speedGaugeIndex: {
        if(mainSportSpeed.speed == 240)
            return mainSportSpeed.speedGaugeImages.length - 1

        for (var i = 1; i < mainSportSpeed.speedGaugeImages.length; i++) {
            if(mainSportSpeed.speedGaugeImages[i-1].speed < mainSportSpeed.speed*0.621371 && mainSportSpeed.speedGaugeImages[i].speed >= mainSportSpeed.speed*0.621371)
            {
                return i
            }
        }
        return 0
    }
}
