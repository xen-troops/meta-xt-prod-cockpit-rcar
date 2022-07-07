FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SUMMARY = "QT Cluster application"
LICENSE = "CLOSED"

SRC_URI = " \
      file://clusterapp.pro \
      file://clusterapp.service \
      file://main.cpp \ 
      file://main.qml \
      file://qml.qrc \
      file://Nav_car.png \
"

DEPENDS += " \
     qtbase \
     qtquickcontrols2 \
     qtquick3d \
     qtdeclarative \
     fonts-deployer \
"

S = "${WORKDIR}"

inherit pkgconfig qmake5 

FILES_${PN} += " \
    ${bindir}/clusterapp \
    ${systemd_system_unitdir}/clusterapp.service \
"

do_install() {
    install -d ${D}/${bindir}
    install -m 0644 ${WORKDIR}/build/clusterapp  ${D}/${bindir}/
    chmod +x ${D}/${bindir}/clusterapp

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/clusterapp.service ${D}${systemd_system_unitdir}/clusterapp.service
}

