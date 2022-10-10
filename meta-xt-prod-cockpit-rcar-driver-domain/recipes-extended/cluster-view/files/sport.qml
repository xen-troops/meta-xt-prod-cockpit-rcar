import QtQuick 2.12
import QtQuick.Window 2.12
import VisClient 1.0

Window {
    id: window
    width: 1920
    height: 720
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint

    VisClient{
        id: vis
        urlValue: "wss://wwwivi:8088"
        onGearValueChanged: {
            for(var i= 0; i < topInfo.gear.length;++i)
            {
                if(vis.gearValue == topInfo.gear[i].gear){
                    topInfo.currentGear = i;
                    return;
                }
            }
        }
    }

    Item {
        id: topInfo
        width: 1920
        height: 720
        anchors.fill: parent
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            Image {
                id: cluster_img
                anchors {
                  bottom: parent.bottom
                }
                source: "images/sport_bckg.png"
                x:0
                y:0
            }
        }
        Item {
            id: speedItem
            x: 660
            y: 70
            width: 599
            height: 576
            Text {
                id:speed
                anchors.centerIn: speedItem
                color: "white"
                font.pixelSize: 100
                text: vis.speedValue.toString()
             }
            Image {
                id: speed_gauge_img
                source : topInfo.speedGaugeImages[topInfo.speedGaugeIndex].source
                anchors.centerIn: speedItem
            }
        }

        Image {
            id: rpm_img
            source : topInfo.rpmGaugeImages[topInfo.currentGauge].source
            x : topInfo.rpmGaugeImages[topInfo.currentGauge].x
            y : topInfo.rpmGaugeImages[topInfo.currentGauge].y
        }

        Image {
            id: power_img
            source :
            {
                if(vis.speedValue == 240)
                    return topInfo.gearGaugeImages[3].source
                return topInfo.gearGaugeImages[Math.trunc(vis.speedValue / 60)].source
            }
            x : {
                if(vis.speedValue == 240)
                    return topInfo.gearGaugeImages[3].x

                return topInfo.gearGaugeImages[Math.trunc(vis.speedValue / 60)].x
            }
            y : {
                if(vis.speedValue == 240)
                    return topInfo.gearGaugeImages[3].y

                return topInfo.gearGaugeImages[Math.trunc(vis.speedValue / 60)].y
            }
        }

        Text {
            id: timeInfo
            x: 40
            y: 40
            color: "white"
            font.pixelSize: 30
            text: {topInfo.timeUpdated;return Qt.formatTime(new Date(), "hh:mm ap")}
        }

        Text {
            id: tripInfo
            x: 40
            y: 653
            color: "white"
            font.pixelSize: 30
            text: "TRIP A 1000 KM"
        }

        Item {
            id: weatherInfo
            x: 1756
            y: 40
            Image {
               id: cloud_img
               anchors.left: parent.left
               anchors.top: weatherInfo.top
               source: "images/Cloudy.png"
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
               source: "images/C.png"
            }
        }
        Item {
            id: odoInfo
            x:1755
            y: 653
            Text {
                id: odo
                anchors.left: odoInfo.left
                color: "white"
                font.pixelSize: 30
                text: qsTr("3378 KM")
            }
        }
        Item {
            id: speedLimitInfo
            x: 430
            y: 137
            Image {
               id: speed_limit_img
               anchors.left: speedLimitInfo.left
               anchors.top: speedLimitInfo.top
               source: "images/Speed_limit_EU_bg_circle.png"
            }
            Text {
                id: speedLimit
                anchors.centerIn: speed_limit_img
                color: "black"
                font.pixelSize: 30
                text: qsTr("50")
            }
        }

        Item {
            id: gearShiftItem
            x: 1393
            y: 304

            Image {
                id: gearShiftRect_img
                source: "images/D_Rectangle.png"
                anchors.left: gearShiftItem.left
                anchors.top: gearShiftItem.top
            }

            Image {
                id: gearShift_img
                source: topInfo.gearShiftImages[topInfo.gearShiftIndex].source
                anchors.centerIn: gearShiftRect_img
            }

            Image{
                id: gearShiftPoint
                source: "images/Gear_change_reminder_point.png"
                anchors.left: gearShiftRect_img.right
                anchors.verticalCenter: gearShiftRect_img.verticalCenter
                anchors.leftMargin: 10
            }
        }

        Image {
            id: gear
            source : topInfo.gear[topInfo.currentGear].source
            x : topInfo.gear[topInfo.currentGear].x
            y : topInfo.gear[topInfo.currentGear].y
        }

        property var rpmGaugeImages : [
            {source: "images/200.png", x: 40, y: 115, rpm: 200},
            {source: "images/400.png", x: 40, y: 115, rom: 400},
            {source: "images/600.png", x: 40, y: 115, rpm: 600},
            {source: "images/800.png", x: 40, y: 115, rpm: 800},
            {source: "images/1000.png", x: 40, y: 115, rpm: 1000},
            {source: "images/1200.png", x: 40, y: 115, rpm: 1200},
            {source: "images/1400.png", x: 40, y: 115, rpm: 1400},
            {source: "images/1600.png", x: 40, y: 115, rpm: 1600},
            {source: "images/1800.png", x: 40, y: 115, rpm: 1800},
            {source: "images/2000.png", x: 40, y: 115, rpm: 2000},
            {source: "images/2200.png", x: 40, y: 115, rpm: 2200},
            {source: "images/2400.png", x: 40, y: 115, rpm: 2400},
            {source: "images/2600.png", x: 40, y: 115, rpm: 2600},
            {source: "images/2800.png", x: 40, y: 115, rpm: 2800},
            {source: "images/3000.png", x: 40, y: 115, rpm: 3000},
            {source: "images/3200.png", x: 40, y: 115, rpm: 3200},
            {source: "images/3400.png", x: 40, y: 115, rpm: 3400},
            {source: "images/3600.png", x: 40, y: 115, rpm: 3600},
            {source: "images/3800.png", x: 40, y: 115, rpm: 3800},
            {source: "images/4000.png", x: 40, y: 115, rpm: 4000},
            {source: "images/4200.png", x: 40, y: 115, rpm: 4200},
            {source: "images/4400.png", x: 40, y: 115, rpm: 4400},
            {source: "images/4600.png", x: 40, y: 115, rpm: 4600},
            {source: "images/4800.png", x: 40, y: 115, rpm: 4800},
            {source: "images/5000.png", x: 40, y: 115, rpm: 5000},
        ]
        property var gearGaugeImages : [
            {source: "images/reminder_Bar_01.png", x: 1440, y: 113},
            {source: "images/reminder_Bar_02.png", x: 1440, y: 113},
            {source: "images/reminder_Bar_03.png", x: 1440, y: 113},
            {source: "images/reminder_Bar_04.png", x: 1440, y: 113},
        ]

        property var speedGaugeImages : [
            {source: "images/8_KM_H.png", x: 749, y: 160, speed: 8},
            {source: "images/15_KM_H.png", x: 749, y: 160, speed: 15 },
            {source: "images/23_KM_H.png", x: 749, y: 160, speed: 23 },
            {source: "images/30_KM_H.png", x: 749, y: 160, speed: 30 },
            {source: "images/38_KM_H.png", x: 749, y: 160, speed: 38 },
            {source: "images/45_KM_H.png", x: 749, y: 160, speed: 45 },
            {source: "images/52_KM_H.png", x: 749, y: 155, speed: 52 },
            {source: "images/60_KM_H.png", x: 749, y: 155, speed: 60 },
            {source: "images/68_KM_H.png", x: 749, y: 155, speed: 68 },
            {source: "images/75_KM_H.png", x: 749, y: 155, speed: 75 },
            {source: "images/82_KM_H.png", x: 749, y: 155, speed: 82 },
            {source: "images/90_KM_H.png", x: 749, y: 155, speed: 90 },
            {source: "images/98_KM_H.png", x: 749, y: 155, speed: 98 },
            {source: "images/105_KM_H.png", x: 749, y: 155, speed: 105 },
            {source: "images/112_KM_H.png", x: 749, y: 155, speed: 112 },
            {source: "images/120_KM_H.png", x: 749, y: 155, speed: 120 },
            {source: "images/128_KM_H.png", x: 749, y: 155, speed: 128 },
            {source: "images/135_KM_H.png", x: 749, y: 155, speed: 135 },
            {source: "images/142_KM_H.png", x: 749, y: 155, speed: 142 },
            {source: "images/150_KM_H.png", x: 749, y: 155, speed: 150 },
            {source: "images/158_KM_H.png", x: 749, y: 155, speed: 158 },
            {source: "images/165_KM_H.png", x: 749, y: 155, speed: 165 },
            {source: "images/172_KM_H.png", x: 749, y: 155, speed: 172 },
            {source: "images/180_KM_H.png", x: 749, y: 155, speed: 180 },
            {source: "images/188_KM_H.png", x: 749, y: 155, speed: 188 },
            {source: "images/195_KM_H.png", x: 749, y: 155, speed: 195 },
            {source: "images/202_KM_H.png", x: 749, y: 155, speed: 202 },
            {source: "images/210_KM_H.png", x: 749, y: 155, speed: 210 },
            {source: "images/218_KM_H.png", x: 749, y: 155, speed: 218 },
            {source: "images/225_KM_H.png", x: 749, y: 155, speed: 225 },
            {source: "images/232_KM_H.png", x: 749, y: 155, speed: 232 },
            {source: "images/240_KM_H.png", x: 749, y: 155, speed: 240 },
        ]

        property var gearShiftImages: [
            {source :"images/D1.png", x: 1393, y: 304, speed: 30},
            {source :"images/D2.png", x: 1393, y: 304, speed: 50},
            {source :"images/D3.png", x: 1393, y: 304, speed: 70},
            {source :"images/D4.png", x: 1393, y: 304, speed: 90},
            {source :"images/D5.png", x: 1393, y: 304, speed: 130},
            {source :"images/D6.png", x: 1393, y: 304, speed: 240},
        ]

        property var gear: [
            {source: "images/Gears_all_off.png", x: 839, y: 639, gear: 5},
            {source: "images/Gears_D.png", x: 839, y: 639, gear: 3},
            {source: "images/Gears_N.png", x: 839, y: 639, gear: 2},
            {source: "images/Gears_P.png", x: 839, y: 639, gear: 0},
            {source: "images/Gears_R.png", x: 839, y: 639, gear: 4},
        ]

        property var timeUpdated: 0
        property var currentGauge: 0
        property var currentGear: 0

        property var speedGaugeIndex: {
            if(vis.speedValue == 240)
                return topInfo.speedGaugeImages.length - 1

            for (var i = 1; i < topInfo.speedGaugeImages.length; i++) {
                if(topInfo.speedGaugeImages[i-1].speed < vis.speedValue && topInfo.speedGaugeImages[i].speed >= vis.speedValue)
                {
                    return i
                }
            }
            return 0
        }
        property var gearShiftIndex: {
            if(vis.speedValue == 240)
                return topInfo.gearShiftImages.length-1

            for (var i = 1; i < topInfo.gearShiftImages.length; i++) {
                if(topInfo.gearShiftImages[i-1].speed < vis.speedValue && topInfo.gearShiftImages[i].speed >= vis.speedValue)
                {
                    return i
                }
            }
            return 0
        }

        Timer {
            interval: 500; running: true/*vis.connectedValue*/; repeat: true
            onTriggered: {
                if(vis.speedValue < 240){
                    vis.speedValue += 5
                    vis.rpmValue = 700 + 17*vis.speedValue
                }
                else {
                    vis.speedValue = 0
                    vis.rpmValue = 700;
                }
                if(vis.gearValue == 3)
                {
                    vis.gearValue = 0;
                }
                else 
                {
                    ++vis.gearValue;
                }
            }
        }

        Timer {
            interval: 60000; running: true; repeat: true
            onTriggered: {
                topInfo.timeUpdated++
            }
        }

        Component.onCompleted: {
            currentGauge = Qt.binding(function(){

                for (var i = 1; i < rpmGaugeImages.length; i++) {
                    if(rpmGaugeImages[i-1].rpm < vis.rpmValue && rpmGaugeImages[i].rpm >= vis.rpmValue)
                    {
                        return i
                    }
                }
                return 0
            }
            )
        }
    }
}
