import QtQuick 2.12
import QtQuick.Window 2.12
import VisClient 1.0
import "./qml/"

Window {
    id: window
    width: 1920
    height: 720
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint

    VisClient{
        id: vis
        urlValue: cmdLine.urlValue
        
        onUrlValueChanged: {
            console.log("NEW Url " + urlValue)
        }

        onGearValueChanged: {
            for(var i= 0; i < footer.gear.length;++i)
            {
                if(vis.gearValue == footer.gear[i].gear){
                    footer.currentGear = i;
                    return;
                }
            }
        }
    }

    Connections{
        target: cmdLine
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
                source: "images/cluster-bkg.png"
                x:0
                y:0
            }
        }
        Item {
            id: speedItem
            x: 380
            y: 215
            width: 320
            height: 80
            Text {
                id:speed
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                font.pixelSize: 100
                text: vis.speedValue.toString()
             }

            Image {
                id: kmh_img
                source: "images/KMH.png"
                anchors.top: speed.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 20
            }
        }

        Item {
            id: rpmItem
            x: 1250
            y: 235
            width: 320
            height: 80
            Text {
                id:rpm
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                y: 235
                color: "white"
                font.pixelSize: 80
                text: vis.rpmValue
             }

            Image {
                id: rpm_img
                source: "images/RPM.png"
                anchors.top: rpm.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 20
            }
        }

        Image {
            id: speed_img
            source : topInfo.speedGauges[topInfo.currentGauge].source
            x : topInfo.speedGauges[topInfo.currentGauge].x
            y : topInfo.speedGauges[topInfo.currentGauge].y
        }

        Image {
            id: power_img
            source :
            {
                if(vis.speedValue == 240)
                    return topInfo.powerGaugeImages[5].source
                return topInfo.powerGaugeImages[Math.trunc(vis.speedValue / 40)].source
            }
            x : {
                if(vis.speedValue == 240)
                    return topInfo.powerGaugeImages[5].x
                return topInfo.powerGaugeImages[Math.trunc(vis.speedValue / 40)].x
            }
            y : {
                if(vis.speedValue == 240)
                    return topInfo.powerGaugeImages[5].y

                return topInfo.powerGaugeImages[Math.trunc(vis.speedValue / 40)].y
            }
        }

        TimeInfo{

        }

        TripInfo{

        }
        WeatherInfo{

        }

        OdoInfo{

        }

        SpeedLimitInfo{

        }

        Footer {
            id: footer
            visible: true
            sport: false
        }

        property var speedGauges : [
            {source: "images/Gauge_Bar_5_with_gauge.png", x: 40, y: 114, speed: 5},
            {source: "images/Gauge_Bar_10_with_gauge.png", x: 40, y: 114, speed: 10},
            {source: "images/Gauge_Bar_20_with_gauge.png", x: 40, y: 114, speed: 20},
            {source: "images/Gauge_Bar_30_with_gauge.png", x: 40, y: 114, speed: 30},
            {source: "images/Gauge_Bar_40_with_gauge.png", x: 40, y: 114, speed: 40},
            {source: "images/Gauge_Bar_50_with_gauge.png", x: 40, y: 114, speed: 50},
            {source: "images/Gauge_Bar_60_with_gauge.png", x: 40, y: 114, speed: 60},
            {source: "images/Gauge_Bar_70_with_gauge.png", x: 40, y: 114, speed: 70},
            {source: "images/Gauge_Bar_80_with_gauge.png", x: 40, y: 114, speed: 80},
            {source: "images/Gauge_Bar_90_with_gauge.png", x: 40, y: 114, speed: 90},
            {source: "images/Gauge_Bar_100_with_gauge.png", x: 40, y: 114, speed: 100},
            {source: "images/Gauge_Bar_110_with_gauge.png", x: 40, y: 114, speed: 110},
            {source: "images/Gauge_Bar_120_with_gauge.png", x: 40, y: 114, speed: 120},
            {source: "images/Gauge_Bar_130_with_gauge.png", x: 40, y: 114, speed: 130},
            {source: "images/Gauge_Bar_140_with_gauge.png", x: 40, y: 114, speed: 140},
            {source: "images/Gauge_Bar_150_with_gauge.png", x: 40, y: 114, speed: 150},
            {source: "images/Gauge_Bar_160_with_gauge.png", x: 40, y: 114, speed: 160},
            {source: "images/Gauge_Bar_170_with_gauge.png", x: 40, y: 114, speed: 170},
            {source: "images/Gauge_Bar_180_with_gauge.png", x: 40, y: 114, speed: 180},
            {source: "images/Gauge_Bar_190_with_gauge.png", x: 40, y: 114, speed: 190},
            {source: "images/Gauge_Bar_200_with_gauge.png", x: 40, y: 114, speed: 200},
            {source: "images/Gauge_Bar_210_with_gauge.png", x: 40, y: 114, speed: 210},
            {source: "images/Gauge_Bar_220_with_gauge.png", x: 40, y: 114, speed: 220},
            {source: "images/Gauge_Bar_230_with_gauge.png", x: 40, y: 114, speed: 230},
            {source: "images/Gauge_Bar_240_with_gauge.png", x: 40, y: 114, speed: 240},
        ]
        property var powerGaugeImages : [
            {source: "images/ECO_1_6_B.png", x: 1387, y: 91},//1550, y: 364/*433*/},
            {source: "images/ECO_2_6_B.png", x: 1387, y: 91},//1550, y: 364/*410*/},
            {source: "images/ECO_3_6_B.png", x: 1387, y: 91},//1550, y: 364/*387*/},
            {source: "images/ECO_4_6_B.png", x: 1387, y: 91},//1550, y: 364},
            {source: "images/ECO_5_6_B.png", x: 1387, y: 91},//1550, y: 341},
            {source: "images/ECO_6_6_B.png", x: 1387, y: 91},//1550, y: 320},
        ]

        property var timeUpdated: 0
        property var currentGauge: 0
        
        Timer {
            interval: 60000; running: !vis.connectedValue; repeat: true
            onTriggered: {
                topInfo.timeUpdated++
            }
        }

        Timer {
            interval: 500; running: !vis.connectedValue; repeat: true
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

                if(!vis.connectedValue){
                    vis.connectTo()
                }
            }
        }
        
        Component.onCompleted: {
            currentGauge = Qt.binding(function(){

                for (var i = 1; i < speedGauges.length; i++) {
                    if(speedGauges[i-1].speed < vis.speedValue && speedGauges[i].speed >= vis.speedValue)
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
