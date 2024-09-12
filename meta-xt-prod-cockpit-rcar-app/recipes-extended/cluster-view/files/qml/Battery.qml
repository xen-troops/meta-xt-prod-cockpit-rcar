import QtQuick 2.0

Item {
    id: mainBattery

    Image {
        id: autoLight
        source : "../images/Battery_icon.png"
        x: 1749
        y: 583
    }

    Image {
        id: batteryGauge
        source: "../images/Battery_Gauge.png"
        x: 1649
        y: 360
    }

    Image {
        id: batteryLevel
        source: "../images/Battery_level.png"
        x: 1649
        y: 440
    }

    Image {
        id: chargeRemider
        source: "../images/Charge_Reminder.png"
        x: 1603
        y: 571
    }

    property var reminder: chargeRemider
}
