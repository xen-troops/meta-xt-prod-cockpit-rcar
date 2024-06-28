import QtQuick 2.12
import QtQuick.Window 2.12
import Model 1.0
import "./qml/"

Window {
    id: window
    width: 1920
    height: 720
    visible: true
    color: "transparent"
    flags: Qt.FramelessWindowHint

    Connections{
        target: model
        onUrlValueChanged: {
            console.log("NEW Url " + urlValue)
        }

        onGearValueChanged: {
            for(var i= 0; i < footer.gear.length;++i)
            {
                if(model.gearValue == footer.gear[i].gear){
                    footer.currentGear = i;
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
            id: cluster_bckg
            anchors.fill: parent
            color: "transparent"
            Image {
                id: cluster_img
                anchors {
                  bottom: parent.bottom
                }
                source: {
                    if(model.modeValue == 2) {
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
            x: 736
            y: 0
            width: 448
            height: 602
            opacity: 1
            visible: model.modeValue == 1 && model.isFirstStart
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
            visible: false
            x:{
                if(model.modeValue == 1)
                {
                    return 580
                }
                return 284
            }
            y:{
                if(mode.modeValue == 1)
                {
                    return 83
                }
                return 130
            }
        }

        Footer {
            id: footer
            visible: true
            sport: model.modeValue == 2
            ready: model.connectedValue
            turn: model.turnValue
        }

        NormalSpeedInfo {
            id: speedInfo
            speed: mdel.speedValue
            visible: model.modeValue == 1
        }

        SportSpeedInfo{
            id:sportSpeedInfo
            speed: model.speedValue
            visible: model.modeValue == 2
        }

        Range{
            id: rangeInfo
            rangeValue: Math.round(300*model.batteryValue/100)
        }

        Battery {
            id: batteryInfo
        }

        EnergyConsumption {
            id: energyConsuptionInfo
        }

        PowerChargeInfo {
            id: powerChargeInfo
            powerValue: 100*model.speedValue/150
            chargeValue: model.batteryValue
            visible: model.modeValue == 2
        }

        property var timeUpdated: 0

        Timer {
            interval: 60000; running: true; repeat: true
            onTriggered: {
                topInfo.timeUpdated++
            }
        }

        Timer {
            id: epamTimer
            interval: 450; repeat: false; running: model.modeValue == 1 && model.isFirstStart == 1 && epam.opacity != 0

            onTriggered: {
                epam.opacity -= 0.01

                if(epam.opacity == 0)
                {
                   epam.visible = false
                   epamTimer.stop()
                }
            }
        }

        Timer {
            interval: 2000; running: !model.connectedValue; repeat: true
            onTriggered: {
                if(!model.connectedValue){
                    model.connectTo()
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
