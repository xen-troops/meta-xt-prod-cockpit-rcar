FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SUMMARY = "QT Cluster application"
LICENSE = "CLOSED"

CLUSTER_DIR="cluster-view-src"

SRC_URI = " \
      file://clusterview.pro;subdir=${CLUSTER_DIR} \
      file://cluster-view.service;subdir=${CLUSTER_DIR} \
      file://main.cpp;subdir=${CLUSTER_DIR} \ 
      file://visclient.h;subdir=${CLUSTER_DIR} \
      file://visclient.cpp;subdir=${CLUSTER_DIR} \
      file://commandline.cpp;subdir=${CLUSTER_DIR} \
      file://commandline.h;subdir=${CLUSTER_DIR} \
      file://ActivatedEvent.cpp;subdir=${CLUSTER_DIR} \
      file://ActivatedEvent.h;subdir=${CLUSTER_DIR} \
      file://main.qml;subdir=${CLUSTER_DIR} \
      file://images/100_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/125_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/14%.png;subdir=${CLUSTER_DIR} \
      file://images/20%.png;subdir=${CLUSTER_DIR} \
      file://images/27_mph.png;subdir=${CLUSTER_DIR} \
      file://images/3_mph.png;subdir=${CLUSTER_DIR} \
      file://images/54%.png;subdir=${CLUSTER_DIR} \
      file://images/6_mph.png;subdir=${CLUSTER_DIR} \
      file://images/84%.png;subdir=${CLUSTER_DIR} \
      file://images/Auto_Lighting_off.png;subdir=${CLUSTER_DIR} \
      file://images/Cloudy.png;subdir=${CLUSTER_DIR} \
      file://images/reminder_Bar_01.png;subdir=${CLUSTER_DIR} \
      file://images/100%.png;subdir=${CLUSTER_DIR} \
      file://images/126mi.png;subdir=${CLUSTER_DIR} \
      file://images/150mi.png;subdir=${CLUSTER_DIR} \
      file://images/210mi.png;subdir=${CLUSTER_DIR} \
      file://images/282mi.png;subdir=${CLUSTER_DIR} \
      file://images/40_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/55_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/6%.png;subdir=${CLUSTER_DIR} \
      file://images/85_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/Auto_Lighting_on.png;subdir=${CLUSTER_DIR} \
      file://images/cluster-bkg.png;subdir=${CLUSTER_DIR} \
      file://images/reminder_Bar_02.png;subdir=${CLUSTER_DIR} \
      file://images/102mi.png;subdir=${CLUSTER_DIR} \
      file://images/126_mph.png;subdir=${CLUSTER_DIR} \
      file://images/150_mph.png;subdir=${CLUSTER_DIR} \
      file://images/216mi.png;subdir=${CLUSTER_DIR} \
      file://images/288mi.png;subdir=${CLUSTER_DIR} \
      file://images/40%.png;subdir=${CLUSTER_DIR} \
      file://images/56%.png;subdir=${CLUSTER_DIR} \
      file://images/70_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/86%.png;subdir=${CLUSTER_DIR} \
      file://images/Bar_1.png;subdir=${CLUSTER_DIR} \
      file://images/Consumption_Gauge.png;subdir=${CLUSTER_DIR} \
      file://images/reminder_Bar_03.png;subdir=${CLUSTER_DIR} \
      file://images/102_mph.png;subdir=${CLUSTER_DIR} \
      file://images/129_mph.png;subdir=${CLUSTER_DIR} \
      file://images/150_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/21_mph.png;subdir=${CLUSTER_DIR} \
      file://images/28%.png;subdir=${CLUSTER_DIR} \
      file://images/42mi.png;subdir=${CLUSTER_DIR} \
      file://images/57_mph.png;subdir=${CLUSTER_DIR} \
      file://images/70%.png;subdir=${CLUSTER_DIR} \
      file://images/87_mph.png;subdir=${CLUSTER_DIR} \
      file://images/Bar_2.png;subdir=${CLUSTER_DIR} \
      file://images/C.png;subdir=${CLUSTER_DIR} \
      file://images/reminder_Bar_04.png;subdir=${CLUSTER_DIR} \
      file://images/105_mph.png;subdir=${CLUSTER_DIR} \
      file://images/12mi.png;subdir=${CLUSTER_DIR} \
      file://images/156mi.png;subdir=${CLUSTER_DIR} \
      file://images/222mi.png;subdir=${CLUSTER_DIR} \
      file://images/294mi.png;subdir=${CLUSTER_DIR} \
      file://images/42_mph.png;subdir=${CLUSTER_DIR} \
      file://images/58%.png;subdir=${CLUSTER_DIR} \
      file://images/72mi.png;subdir=${CLUSTER_DIR} \
      file://images/88%.png;subdir=${CLUSTER_DIR} \
      file://images/Bar_3.png;subdir=${CLUSTER_DIR} \
      file://images/Cruise_control_on.png;subdir=${CLUSTER_DIR} \
      file://images/RPM.png;subdir=${CLUSTER_DIR} \
      file://images/105_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/12_mph.png;subdir=${CLUSTER_DIR} \
      file://images/15_mph.png;subdir=${CLUSTER_DIR} \
      file://images/228mi.png;subdir=${CLUSTER_DIR} \
      file://images/2%.png;subdir=${CLUSTER_DIR} \
      file://images/42%.png;subdir=${CLUSTER_DIR} \
      file://images/5_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/72_mph.png;subdir=${CLUSTER_DIR} \
      file://images/8%.png;subdir=${CLUSTER_DIR} \
      file://images/Bar_4.png;subdir=${CLUSTER_DIR} \
      file://images/epam.png;subdir=${CLUSTER_DIR} \
      file://images/Speed_gauge.png;subdir=${CLUSTER_DIR} \
      file://images/108mi.png;subdir=${CLUSTER_DIR} \
      file://images/12%.png;subdir=${CLUSTER_DIR} \
      file://images/15_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/22%.png;subdir=${CLUSTER_DIR} \
      file://images/300mi.png;subdir=${CLUSTER_DIR} \
      file://images/44%.png;subdir=${CLUSTER_DIR} \
      file://images/60mi.png;subdir=${CLUSTER_DIR} \
      file://images/72%.png;subdir=${CLUSTER_DIR} \
      file://images/90mi.png;subdir=${CLUSTER_DIR} \
      file://images/Battery_Gauge.png;subdir=${CLUSTER_DIR} \
      file://images/Gears_all_off.png;subdir=${CLUSTER_DIR} \
      file://images/Speed_limit_EU_bg_circle.png;subdir=${CLUSTER_DIR} \
      file://images/108_mph.png;subdir=${CLUSTER_DIR} \
      file://images/130_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/162mi.png;subdir=${CLUSTER_DIR} \
      file://images/234mi.png;subdir=${CLUSTER_DIR} \
      file://images/30mi.png;subdir=${CLUSTER_DIR} \
      file://images/45_mph.png;subdir=${CLUSTER_DIR} \
      file://images/60_mph.png;subdir=${CLUSTER_DIR} \
      file://images/74%.png;subdir=${CLUSTER_DIR} \
      file://images/90_mph.png;subdir=${CLUSTER_DIR} \
      file://images/Battery_icon.png;subdir=${CLUSTER_DIR} \
      file://images/Gears_D.png;subdir=${CLUSTER_DIR} \
      file://images/Speed_limit_indicator_US.png;subdir=${CLUSTER_DIR} \
      file://images/10_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/132mi.png;subdir=${CLUSTER_DIR} \
      file://images/168mi.png;subdir=${CLUSTER_DIR} \
      file://images/240mi.png;subdir=${CLUSTER_DIR} \
      file://images/30_mph.png;subdir=${CLUSTER_DIR} \
      file://images/45_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/60_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/75_mph.png;subdir=${CLUSTER_DIR} \
      file://images/90_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/Battery_level.png;subdir=${CLUSTER_DIR} \
      file://images/Gears_N.png;subdir=${CLUSTER_DIR} \
      file://images/sport_bckg.png;subdir=${CLUSTER_DIR} \
      file://images/10%.png;subdir=${CLUSTER_DIR} \
      file://images/132_mph.png;subdir=${CLUSTER_DIR} \
      file://images/16%.png;subdir=${CLUSTER_DIR} \
      file://images/246mi.png;subdir=${CLUSTER_DIR} \
      file://images/30_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/46%.png;subdir=${CLUSTER_DIR} \
      file://images/60%.png;subdir=${CLUSTER_DIR} \
      file://images/75_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/90%.png;subdir=${CLUSTER_DIR} \
      file://images/Charge_Reminder.png;subdir=${CLUSTER_DIR} \
      file://images/Gears_P.png;subdir=${CLUSTER_DIR} \
      file://images/SPORT_off.png;subdir=${CLUSTER_DIR} \
      file://images/110_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/135_mph.png;subdir=${CLUSTER_DIR} \
      file://images/174mi.png;subdir=${CLUSTER_DIR} \
      file://images/24mi.png;subdir=${CLUSTER_DIR} \
      file://images/30%.png;subdir=${CLUSTER_DIR} \
      file://images/48mi.png;subdir=${CLUSTER_DIR} \
      file://images/62%.png;subdir=${CLUSTER_DIR} \
      file://images/76%.png;subdir=${CLUSTER_DIR} \
      file://images/92%.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_100%.png;subdir=${CLUSTER_DIR} \
      file://images/Gears_R.png;subdir=${CLUSTER_DIR} \
      file://images/SPORT_on.png;subdir=${CLUSTER_DIR} \
      file://images/111_mph.png;subdir=${CLUSTER_DIR} \
      file://images/135_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/180mi.png;subdir=${CLUSTER_DIR} \
      file://images/24_mph.png;subdir=${CLUSTER_DIR} \
      file://images/32%.png;subdir=${CLUSTER_DIR} \
      file://images/48_mph.png;subdir=${CLUSTER_DIR} \
      file://images/63_mph.png;subdir=${CLUSTER_DIR} \
      file://images/78mi.png;subdir=${CLUSTER_DIR} \
      file://images/93_mph.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_10%.png;subdir=${CLUSTER_DIR} \
      file://images/kWh.png;subdir=${CLUSTER_DIR} \
      file://images/Temperature_level.png;subdir=${CLUSTER_DIR} \
      file://images/114mi.png;subdir=${CLUSTER_DIR} \
      file://images/138mi.png;subdir=${CLUSTER_DIR} \
      file://images/186mi.png;subdir=${CLUSTER_DIR} \
      file://images/24%.png;subdir=${CLUSTER_DIR} \
      file://images/33_mph.png;subdir=${CLUSTER_DIR} \
      file://images/48%.png;subdir=${CLUSTER_DIR} \
      file://images/64%.png;subdir=${CLUSTER_DIR} \
      file://images/78_mph.png;subdir=${CLUSTER_DIR} \
      file://images/94%.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_20%.png;subdir=${CLUSTER_DIR} \
      file://images/mi.png;subdir=${CLUSTER_DIR} \
      file://images/Turn_left_off.png;subdir=${CLUSTER_DIR} \
      file://images/114_mph.png;subdir=${CLUSTER_DIR} \
      file://images/138_mph.png;subdir=${CLUSTER_DIR} \
      file://images/18mi.png;subdir=${CLUSTER_DIR} \
      file://images/252mi.png;subdir=${CLUSTER_DIR} \
      file://images/34%.png;subdir=${CLUSTER_DIR} \
      file://images/4%.png;subdir=${CLUSTER_DIR} \
      file://images/65_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/78%.png;subdir=${CLUSTER_DIR} \
      file://images/95_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_30%.png;subdir=${CLUSTER_DIR} \
      file://images/mph.png;subdir=${CLUSTER_DIR} \
      file://images/Turn_left_on.png;subdir=${CLUSTER_DIR} \
      file://images/115_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/140_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/18_mph.png;subdir=${CLUSTER_DIR} \
      file://images/258mi.png;subdir=${CLUSTER_DIR} \
      file://images/35_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/50_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/66mi.png;subdir=${CLUSTER_DIR} \
      file://images/80_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/96mi.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_40%.png;subdir=${CLUSTER_DIR} \
      file://images/Outline.png;subdir=${CLUSTER_DIR} \
      file://images/Turn_right_off.png;subdir=${CLUSTER_DIR} \
      file://images/117_mph.png;subdir=${CLUSTER_DIR} \
      file://images/141_mph.png;subdir=${CLUSTER_DIR} \
      file://images/18%.png;subdir=${CLUSTER_DIR} \
      file://images/25_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/36mi.png;subdir=${CLUSTER_DIR} \
      file://images/50%.png;subdir=${CLUSTER_DIR} \
      file://images/66_mph.png;subdir=${CLUSTER_DIR} \
      file://images/80%.png;subdir=${CLUSTER_DIR} \
      file://images/96_mph.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_50%.png;subdir=${CLUSTER_DIR} \
      file://images/Power_CHG_Gauge.png;subdir=${CLUSTER_DIR} \
      file://images/Turn_right_on.png;subdir=${CLUSTER_DIR} \
      file://images/120mi.png;subdir=${CLUSTER_DIR} \
      file://images/144mi.png;subdir=${CLUSTER_DIR} \
      file://images/192mi.png;subdir=${CLUSTER_DIR} \
      file://images/264mi.png;subdir=${CLUSTER_DIR} \
      file://images/36_mph.png;subdir=${CLUSTER_DIR} \
      file://images/51_mph.png;subdir=${CLUSTER_DIR} \
      file://images/66%.png;subdir=${CLUSTER_DIR} \
      file://images/81_mph.png;subdir=${CLUSTER_DIR} \
      file://images/96%.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_60%.png;subdir=${CLUSTER_DIR} \
      file://images/Power_Gauge.png;subdir=${CLUSTER_DIR} \
      file://images/120_mph.png;subdir=${CLUSTER_DIR} \
      file://images/144_mph.png;subdir=${CLUSTER_DIR} \
      file://images/198mi.png;subdir=${CLUSTER_DIR} \
      file://images/26%.png;subdir=${CLUSTER_DIR} \
      file://images/36%.png;subdir=${CLUSTER_DIR} \
      file://images/52%.png;subdir=${CLUSTER_DIR} \
      file://images/68%.png;subdir=${CLUSTER_DIR} \
      file://images/82%.png;subdir=${CLUSTER_DIR} \
      file://images/98%.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_70%.png;subdir=${CLUSTER_DIR} \
      file://images/Range_gauge.png;subdir=${CLUSTER_DIR} \
      file://images/120_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/145_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/204mi.png;subdir=${CLUSTER_DIR} \
      file://images/270mi.png;subdir=${CLUSTER_DIR} \
      file://images/38%.png;subdir=${CLUSTER_DIR} \
      file://images/54mi.png;subdir=${CLUSTER_DIR} \
      file://images/69_mph.png;subdir=${CLUSTER_DIR} \
      file://images/84mi.png;subdir=${CLUSTER_DIR} \
      file://images/99_mph.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_80%.png;subdir=${CLUSTER_DIR} \
      file://images/READY_off.png;subdir=${CLUSTER_DIR} \
      file://images/123_mph.png;subdir=${CLUSTER_DIR} \
      file://images/147_mph.png;subdir=${CLUSTER_DIR} \
      file://images/20_MPH.png;subdir=${CLUSTER_DIR} \
      file://images/276mi.png;subdir=${CLUSTER_DIR} \
      file://images/39_mph.png;subdir=${CLUSTER_DIR} \
      file://images/54_mph.png;subdir=${CLUSTER_DIR} \
      file://images/6mi.png;subdir=${CLUSTER_DIR} \
      file://images/84_mph.png;subdir=${CLUSTER_DIR} \
      file://images/9_mph.png;subdir=${CLUSTER_DIR} \
      file://images/CHG_Bar_90%.png;subdir=${CLUSTER_DIR} \
      file://images/READY_on.png;subdir=${CLUSTER_DIR} \
      file://qml.qrc;subdir=${CLUSTER_DIR} \
      file://qml/Battery.qml;subdir=${CLUSTER_DIR} \
      file://qml/EnergyConsumption.qml;subdir=${CLUSTER_DIR} \
      file://qml/Footer.qml;subdir=${CLUSTER_DIR} \
      file://qml/NormalSpeedInfo.qml;subdir=${CLUSTER_DIR} \
      file://qml/OdoInfo.qml;subdir=${CLUSTER_DIR} \
      file://qml/PowerChargeInfo.qml;subdir=${CLUSTER_DIR} \
      file://qml/Range.qml;subdir=${CLUSTER_DIR} \
      file://qml/SpeedLimitInfo.qml;subdir=${CLUSTER_DIR} \
      file://qml/SportSpeedInfo.qml;subdir=${CLUSTER_DIR} \
      file://qml/TimeInfo.qml;subdir=${CLUSTER_DIR} \
      file://qml/TripInfo.qml;subdir=${CLUSTER_DIR} \
      file://qml/WeatherInfo.qml;subdir=${CLUSTER_DIR} \
"

DEPENDS += " \
     qtbase \
     qtquickcontrols2 \
     qtquick3d \
     qtdeclarative \
     fonts-deployer \
     qtwebsockets \
"

S = "${WORKDIR}/${CLUSTER_DIR}"

inherit pkgconfig qmake5 systemd

SYSTEMD_SERVICE:${PN} = "cluster-view.service"

FILES:${PN} += " \
    ${bindir}/clusterview \
    ${systemd_system_unitdir}/cluster-view.service \
"

do_install() {
    install -d ${D}/${bindir}
    install -m 0644 ${WORKDIR}/build/clusterview  ${D}/${bindir}/
    chmod +x ${D}/${bindir}/clusterview

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/${CLUSTER_DIR}/cluster-view.service ${D}${systemd_system_unitdir}/cluster-view.service
}

