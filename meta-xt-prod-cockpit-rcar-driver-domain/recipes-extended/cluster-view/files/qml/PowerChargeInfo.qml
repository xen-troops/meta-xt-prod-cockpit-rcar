import QtQuick 2.0

Item {
    id: powerChargeMain
    Image {
        id: powerChargeGauge
        x: 40
        y: 114
        source: "../images/Power_CHG_Gauge.png"
    }

    Image{
        id: powerImg
        source: dummyPower.source
        x: 465 - dummyPower.width
        y: 630 - dummyPower.height
    }

    Image{
        id: dummyPower
        source : powerChargeMain.powerGauges[powerChargeMain.currentPower].source
        visible: false
    }

    Image{
        id: chargeImg
        source: dummyCharge.source
        x: 540 - dummyCharge.width
        y: 620 - dummyCharge.height
    }

    Image{
        id: dummyCharge
        source : powerChargeMain.chargeGauges[powerChargeMain.currentCharge].source
        visible: false
    }

    Text{
        id: chargeValue
        x: 390
        y: 280
        text: (currentCharge* 10).toString()
        color: "lightblue"
        font.pixelSize: 100
    }

    Text{
        id: chargePValue
        text: "%"
        color: "grey"
        font.pixelSize: 30
        anchors.left: chargeValue.right
        anchors.bottom: chargeValue.bottom
        anchors.leftMargin: 20
        anchors.bottomMargin: 15
    }

    property var powerValue: 100
    property var chargeValue: 100
    property var currentPower: 0
    property var currentCharge: 0

    property var powerGauges:[
        {source: "../images/2%.png", power: 2},
        {source: "../images/4%.png", power: 4},
        {source: "../images/6%.png", power: 6},
        {source: "../images/8%.png", power: 8},
        {source: "../images/10%.png", power: 10},
        {source: "../images/12%.png", power: 12},
        {source: "../images/14%.png", power: 14},
        {source: "../images/16%.png", power: 16},
        {source: "../images/18%.png", power: 18},
        {source: "../images/20%.png", power: 20},
        {source: "../images/22%.png", power: 22},
        {source: "../images/24%.png", power: 24},
        {source: "../images/26%.png", power: 26},
        {source: "../images/28%.png", power: 28},
        {source: "../images/30%.png", power: 30},
        {source: "../images/32%.png", power: 32},
        {source: "../images/34%.png", power: 34},
        {source: "../images/36%.png", power: 36},
        {source: "../images/38%.png", power: 38},
        {source: "../images/40%.png", power: 40},
        {source: "../images/42%.png", power: 42},
        {source: "../images/44%.png", power: 44},
        {source: "../images/46%.png", power: 46},
        {source: "../images/48%.png", power: 48},
        {source: "../images/50%.png", power: 50},
        {source: "../images/52%.png", power: 52},
        {source: "../images/54%.png", power: 54},
        {source: "../images/56%.png", power: 56},
        {source: "../images/58%.png", power: 58},
        {source: "../images/60%.png", power: 60},
        {source: "../images/62%.png", power: 62},
        {source: "../images/64%.png", power: 64},
        {source: "../images/66%.png", power: 66},
        {source: "../images/68%.png", power: 68},
        {source: "../images/70%.png", power: 70},
        {source: "../images/72%.png", power: 72},
        {source: "../images/74%.png", power: 74},
        {source: "../images/76%.png", power: 76},
        {source: "../images/78%.png", power: 78},
        {source: "../images/80%.png", power: 80},
        {source: "../images/82%.png", power: 82},
        {source: "../images/84%.png", power: 84},
        {source: "../images/86%.png", power: 86},
        {source: "../images/88%.png", power: 88},
        {source: "../images/90%.png", power: 90},
        {source: "../images/92%.png", power: 92},
        {source: "../images/94%.png", power: 94},
        {source: "../images/96%.png", power: 96},
        {source: "../images/98%.png", power: 98},
        {source: "../images/100%.png", power: 100},
    ]
    property var chargeGauges:[
        {source: "../images/CHG_Bar_10%.png", charge: 10},
        {source: "../images/CHG_Bar_20%.png", charge: 20},
        {source: "../images/CHG_Bar_30%.png", charge: 30},
        {source: "../images/CHG_Bar_40%.png", charge: 40},
        {source: "../images/CHG_Bar_50%.png", charge: 50},
        {source: "../images/CHG_Bar_60%.png", charge: 60},
        {source: "../images/CHG_Bar_70%.png", charge: 70},
        {source: "../images/CHG_Bar_80%.png", charge: 80},
        {source: "../images/CHG_Bar_90%.png", charge: 90},
        {source: "../images/CHG_Bar_100%.png", charge: 100},
    ]

    Component.onCompleted: {
        powerChargeMain.currentPower = Qt.binding(function(){
            for (var i = 1; i < powerChargeMain.powerGauges.length; i++) {
                if(powerChargeMain.powerGauges[i-1].power < Math.round(powerChargeMain.powerValue) &&
                        powerChargeMain.powerGauges[i].power >= Math.round(powerChargeMain.powerValue))
                {
                    return i
                }
            }
            return 0
        }
        )

        powerChargeMain.currentCharge = Qt.binding(function(){
            for (var i = 1; i < powerChargeMain.chargeGauges.length; i++) {
                if(powerChargeMain.chargeGauges[i-1].charge < Math.round(powerChargeMain.chargeValue) &&
                        powerChargeMain.chargeGauges[i].charge >= Math.round(powerChargeMain.chargeValue))
                {
                    return i
                }
            }
            return 0
        }
        )
    }
}
