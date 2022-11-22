FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SUMMARY = "QT Cluster application"
LICENSE = "CLOSED"

SRC_URI = " \
      file://clusterview.pro \
      file://cluster-view.service \
      file://main.cpp \ 
      file://visclient.h \
      file://visclient.cpp \
      file://commandline.cpp \
      file://commandline.h \
      file://main.qml \
      file://qml.qrc \
      file://images/cluster-bkg.png \
      file://images/Cloudy.png \
      file://images/ECO_5_6_A.png \
      file://images/Gauge_Bar_160_with_gauge.png  \
      file://images/Gauge_Bar_40_with_gauge.png \
      file://images/cluster-bkg.png  \
      file://images/ECO_5_6_B.png \
      file://images/Gauge_Bar_170_with_gauge.png \
      file://images/Gauge_Bar_50_with_gauge.png \
      file://images/C.png \
      file://images/ECO_6_6_A.png \
      file://images/Gauge_Bar_180_with_gauge.png \
      file://images/Gauge_Bar_5_with_gauge.png \
      file://images/ECO_1_6_A.png \
      file://images/ECO_6_6_B.png \
      file://images/Gauge_Bar_190_with_gauge.png \
      file://images/Gauge_Bar_60_with_gauge.png \
      file://images/ECO_1_6_B.png \
      file://images/Gauge_Bar_100_with_gauge.png \
      file://images/Gauge_Bar_200_with_gauge.png \
      file://images/Gauge_Bar_70_with_gauge.png \
      file://images/ECO_2_6_A.png \
      file://images/Gauge_Bar_10_with_gauge.png \
      file://images/Gauge_Bar_20_with_gauge.png \
      file://images/Gauge_Bar_80_with_gauge.png \
      file://images/ECO_2_6_B.png \
      file://images/Gauge_Bar_110_with_gauge.png \
      file://images/Gauge_Bar_210_with_gauge.png \
      file://images/Gauge_Bar_90_with_gauge.png \
      file://images/ECO_3_6_A.png \
      file://images/Gauge_Bar_120_with_gauge.png \
      file://images/Gauge_Bar_220_with_gauge.png \
      file://images/KMH.png \
      file://images/ECO_3_6_B.png \
      file://images/Gauge_Bar_130_with_gauge.png \
      file://images/Gauge_Bar_230_with_gauge.png \
      file://images/RPM.png \
      file://images/ECO_4_6_A.png \
      file://images/Gauge_Bar_140_with_gauge.png \
      file://images/Gauge_Bar_240_with_gauge.png \
      file://images/Speed_limit_EU_bg_circle.png \
      file://images/ECO_4_6_B.png \
      file://images/Gauge_Bar_150_with_gauge.png \
      file://images/Gauge_Bar_30_with_gauge.png \
      file://images/1000.png \
      file://images/105_KM_H.png \
      file://images/112_KM_H.png \
      file://images/1200.png \
      file://images/120_KM_H.png \
      file://images/128_KM_H.png \
      file://images/135_KM_H.png \
      file://images/1400.png \
      file://images/142_KM_H.png \
      file://images/150_KM_H.png \
      file://images/158_KM_H.png \
      file://images/15_KM_H.png \
      file://images/1600.png \
      file://images/165_KM_H.png \
      file://images/172_KM_H.png \
      file://images/1800.png \
      file://images/180_KM_H.png \
      file://images/188_KM_H.png \
      file://images/195_KM_H.png \
      file://images/200.png \
      file://images/2000.png \
      file://images/202_KM_H.png \
      file://images/210_KM_H.png \
      file://images/218_KM_H.png \
      file://images/2200.png \
      file://images/225_KM_H.png \
      file://images/232_KM_H.png \
      file://images/23_KM_H.png \
      file://images/2400.png \
      file://images/240_KM_H.png \
      file://images/2600.png \
      file://images/2800.png \
      file://images/3000.png \
      file://images/30_KM_H.png \
      file://images/3200.png \
      file://images/3400.png \
      file://images/3600.png \
      file://images/3800.png \
      file://images/38_KM_H.png \
      file://images/400.png \
      file://images/4000.png \
      file://images/4200.png \
      file://images/4400.png \
      file://images/45_KM_H.png \
      file://images/4600.png \
      file://images/4800.png \
      file://images/5000.png \
      file://images/5200.png \
      file://images/52_KM_H.png \
      file://images/5400.png \
      file://images/5600.png \
      file://images/5800.png \
      file://images/600.png \
      file://images/6000.png \
      file://images/60_KM_H.png \
      file://images/6200.png \
      file://images/6400.png \
      file://images/6600.png \
      file://images/6800.png \
      file://images/68_KM_H.png \
      file://images/7000.png \
      file://images/75_KM_H.png \
      file://images/800.png \
      file://images/82_KM_H.png \
      file://images/8_KM_H.png \
      file://images/90_KM_H.png \
      file://images/98_KM_H.png \
      file://images/Bar_1.png \
      file://images/Bar_2.png \
      file://images/Bar_3.png \
      file://images/Bar_4.png \
      file://images/D1.png \
      file://images/D2.png \
      file://images/D3.png \
      file://images/D4.png \
      file://images/D5.png \
      file://images/D6.png \
      file://images/reminder_Bar_01.png \
      file://images/reminder_Bar_02.png \
      file://images/reminder_Bar_03.png \
      file://images/reminder_Bar_04.png \
      file://images/sport_bckg.png \
      file://sport.qml \
      file://images/Gear_change_reminder_point.png \
      file://images/D_Rectangle.png \
      file://images/Gears_all_off.png \
      file://images/Gears_D.png \
      file://images/Gears_P.png \
      file://images/Gears_N.png \
      file://images/Gears_R.png \
      file://images/Cruise_control_on.png \
      file://images/Turn_left_off.png \
      file://images/Auto_Lighting_off.png \
      file://images/Turn_right_off.png \
      file://images/Auto_Lighting_on.png \
      file://images/SPORT_on.png \
      file://images/SPORT_off.png \
      file://qml/Footer.qml \
      file://qml/Footer.qml \
      file://qml/OdoInfo.qml \
      file://qml/SpeedLimitInfo.qml \
      file://qml/TimeInfo.qml \
      file://qml/TripInfo.qml \
      file://qml/WeatherInfo.qml \      
"

DEPENDS += " \
     qtbase \
     qtquickcontrols2 \
     qtquick3d \
     qtdeclarative \
     fonts-deployer \
     qtwebsockets \
"

S = "${WORKDIR}"

inherit pkgconfig qmake5 systemd

SYSTEMD_SERVICE_${PN} = "cluster-view.service"

FILES_${PN} += " \
    ${bindir}/clusterview \
    ${systemd_system_unitdir}/cluster-view.service \
"

do_install() {
    install -d ${D}/${bindir}
    install -m 0644 ${WORKDIR}/build/clusterview  ${D}/${bindir}/
    chmod +x ${D}/${bindir}/clusterview

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/cluster-view.service ${D}${systemd_system_unitdir}/cluster-view.service
}

