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
                console.log(" SRC Gear Value " + vis.gearValue + " comparing with " + footer.gear[i].gear)
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
        opacity: cmdLine.getMode() == 1 && cmdLine.firstStart ? 0 : 1
        Rectangle {
            id: cluster_bckg
            anchors.fill: parent
            color: "transparent"
            Image {
                id: cluster_img
                anchors {
                  bottom: parent.bottom
                }
                source: {
                    if(cmdLine.modeValue == 2) {
                        return "images/sport_bckg.png"
                    }
                    return "images/cluster-bkg.png"
                }
                x:0
                y:0
                opacity: 1
            }
        }

        Image {
            id: epam
            source : "images/epam.png"
            x: 707
            y: 10
            opacity: 1
            visible: cmdLine.getMode() == 1 && cmdLine.firstStart == 1
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
            x:{
                if(cmdLine.getMode() == 1)
                {
                    return 580
                }
                return 284
            }
            y:{
                if(cmdLine.getMode() == 1)
                {
                    return 83
                }
                return 130
            }
        }

        Footer {
            id: footer
            visible: true
            sport: cmdLine.getMode() == 2
            ready: vis.connectedValue
            turn: vis.turnValue
        }

        NormalSpeedInfo {
            id: speedInfo
            speed: vis.speedValue
            visible: cmdLine.getMode() == 1
        }

        SportSpeedInfo{
            id:sportSpeedInfo
            speed: vis.speedValue
            visible: cmdLine.getMode() == 2
        }

        Range{
            id: rangeInfo
            rangeValue: Math.round(300*vis.batteryValue/100)
        }

        Battery {
            id: batteryInfo
        }

        EnergyConsumption {
            id: energyConsuptionInfo
        }

        PowerChargeInfo {
            id: powerChargeInfo
            powerValue: vis.batteryValue
            chargeValue: vis.batteryValue
            visible: cmdLine.getMode() == 2
        }

        property var timeUpdated: 0

        Timer {
            interval: 60000; running: !vis.connectedValue; repeat: true
            onTriggered: {
                topInfo.timeUpdated++
            }
        }

        Timer {
            id: epamTimer
            interval: 450; repeat: false; running: cmdLine.getMode() == 1 && cmdLine.firstStart == 1 && epam.opacity != 0

            onTriggered: {
                epam.opacity -= 0.01

                if(epam.opacity == 0)
                {
                   epam.visible = false
                   epamTimer.stop()
                }
                console.log("!!!Background opacity " + topInfo.opacity)
                if(topInfo.opacity != 1)
                {
                    topInfo.opacity += 0.1
                }
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

                if(vis.batteryValue != 0)
                {
                    vis.batteryValue -= 1
                }
                else
                {
                    vis.batteryValue = 100
                }

                if(powerChargeInfo.powerValue > 0)
                {
                    --powerChargeInfo.powerValue
                }
                else
                {
                    powerChargeInfo.powerValue = 100
                }

                if(powerChargeInfo.chargeValue > 0)
                {
                    --powerChargeInfo.chargeValue
                }
                else
                {
                    powerChargeInfo.chargeValue = 100
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
            batteryInfo.reminder.visible = Qt.binding(function(){
                return rangeInfo.rangeValue < 40
            }
            )
        }
    }
}
