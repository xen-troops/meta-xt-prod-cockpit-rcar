import QtQuick 2.0

Item {
    id: footer
    property var turn: -1
    Image {
        id: gear
        source : footer.gear[footer.currentGear].source
        x : footer.gear[footer.currentGear].x
        y : footer.gear[footer.currentGear].y
    }

    Image {
        id: sport
        source : {
            if(footer.sport)
            {
                return "../images/SPORT_on.png"
            }
            else
            {
                return "../images/SPORT_off.png"
            }
        }
        x: 1127
        y: 639
    }

    Image {
        id: cruis
        source : "../images/Cruise_control_on.png"
        x: 648
        y: 645
    }

    Image {
        id: readiness
        source : {
            if(ready)
            {
                return "../images/READY_on.png"
            }
            else
            {
                return "../images/READY_off.png"
            }
        }
        x: 710
        y: 642
    }

    Image {
        id: turnLeft
        source: "../images/Turn_left_off.png"
        x: 571
        y: 639
    }

    Image {
        id: turnRight
        source: "../images/Turn_right_off.png"
        x: 1309
        y: 639
    }

    Image {
        id: turnLeftOn
        source: "../images/Turn_left_on.png"
        x: 571
        y: 639
        visible: turn == 2 || turnLeftTimer.counter > 0 && turnLeftTimer.counter <= 6
        onVisibleChanged:{
            if(visible){
                turnLeftTimer.counter = 1
            }
        }
    }

    Image {
        id: turnRightOn
        source: "../images/Turn_right_on.png"
        x: 1309
        y: 639
        visible: turn == 1 || turnRightTimer.counter > 0 && turnRightTimer.counter <= 6
        onVisibleChanged:{
            if(visible){
                turnRightTimer.counter = 1
            }
        }
    }

    Timer
    {
        id: turnRightTimer
        property var counter: 0
        interval: 500; repeat: true;
        running: counter > 0 && counter <= 6
        onCounterChanged: {
            if(counter > 6)
            {
                counter = 0
            }
        }

        onTriggered: {
            if(turnRightOn.opacity == 1)
            {
                turnRightOn.opacity = 0
            }
            else
            {
                turnRightOn.opacity = 1
            }
            ++counter
            console.log("Right counter " + counter)
        }
    }

    Timer
    {
        id: turnLeftTimer
        property var counter: 0

        interval: 1000
        repeat: true
        running: counter > 0 && counter <= 6

        onCounterChanged: {
            if(counter > 6)
            {
                counter = 0
            }
        }

        onTriggered: {
            if(turnLeftOn.opacity == 1)
            {
                turnLeftOn.opacity = 0
            }
            else
            {
                turnLeftOn.opacity = 1
            }
            ++counter
            console.log("Left counter " + counter + "  opacity " + turnLeftOn.opacity)
        }
    }

    property var gear: [
        {source: "../images/Gears_all_off.png", x: 839, y: 629/*639*/, gear: 10},
        {source: "../images/Gears_D.png", x: 839, y: 629/*639*/, gear: 3},
        {source: "../images/Gears_N.png", x: 839, y: 629/*639*/, gear: 2},
        {source: "../images/Gears_P.png", x: 839, y: 629/*639*/, gear: 0},
        {source: "../images/Gears_R.png", x: 839, y: 629/*639*/, gear: 5},
    ]
    property bool ready: false
    property var currentGear: 0
    property bool sport: false
}
