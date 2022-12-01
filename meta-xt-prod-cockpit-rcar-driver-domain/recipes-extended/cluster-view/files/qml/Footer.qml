import QtQuick 2.0

Item {
    id: footer
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
        x: 1127//1137
        y: 639//643
    }
/*
    Image {
        id: autoLight
        source : "../images/Auto_Lighting_on.png"
        x: 740
        y: 643
    }
*/
    Image {
        id: cruis
        source : "../images/Cruise_control_on.png"
        x: 648//680
        y: 645//643
    }

    Image {
        id: readiness
        source : {
            if(readiness)
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
        x: 571//596
        y: 639//638
    }

    Image {
        id: turnRight
        source: "../images/Turn_right_off.png"
        x: 1309//1284
        y: 639//638
    }

    property var gear: [
        {source: "../images/Gears_all_off.png", x: 839, y: 629/*639*/, gear: 5},
        {source: "../images/Gears_D.png", x: 839, y: 629/*639*/, gear: 3},
        {source: "../images/Gears_N.png", x: 839, y: 629/*639*/, gear: 2},
        {source: "../images/Gears_P.png", x: 839, y: 629/*639*/, gear: 0},
        {source: "../images/Gears_R.png", x: 839, y: 629/*639*/, gear: 4},
    ]
    property var readiness: false
    property var currentGear: 0
    property bool sport: false
}
