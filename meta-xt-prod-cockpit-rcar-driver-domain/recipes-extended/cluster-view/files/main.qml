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
                source: {
                    if(cmdLine.modeValue == 2) {
                        return "images/sport_bckg.png"
                    }
                    return "images/cluster-bkg.png"
                }
                x:0
                y:0
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
            x:{
                if(cmdLine.getMode() == 1)
                {
                    return 658
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
            readiness: false
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
            rangeValue: 300
        }

        Battery {
            id: batteryInfo
        }

        EnergyConsumption {
            id: energyConsuptionInfo
        }

        PowerChargeInfo {
            id: powerChargeInfo
            powerValue: 100
            chargeValue: 100
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
                if(rangeInfo.rangeValue > 0){
                    rangeInfo.rangeValue -= 5
                }
                else {
                    rangeInfo.rangeValue = 300
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

            footer.readiness = Qt.binding(function(){
                return vis.speedValue > 0
            }
            )
        }
    }
}
