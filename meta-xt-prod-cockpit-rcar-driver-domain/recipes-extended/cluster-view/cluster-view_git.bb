FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SUMMARY = "QT Cluster application"
LICENSE = "CLOSED"

CLUSTER_DIR="cluster-view-src"

SRC_URI = " \
      file://clusterview.pro;subdir=${CLUSTER_DIR} \
      file://cluster-view.service;subdir=${CLUSTER_DIR} \
      file://main.cpp;subdir=${CLUSTER_DIR} \ 
      file://Model.h;subdir=${CLUSTER_DIR} \
      file://Model.cpp;subdir=${CLUSTER_DIR} \
      file://Consumers.cpp;subdir=${CLUSTER_DIR} \
      file://Consumers.h;subdir=${CLUSTER_DIR} \
      file://VisSocket.h;subdir=${CLUSTER_DIR} \
      file://VisSocket.cpp;subdir=${CLUSTER_DIR} \
      file://QtVisSocket.cpp;subdir=${CLUSTER_DIR} \
      file://QtVisSocket.h;subdir=${CLUSTER_DIR} \
      file://ActivatedEvent.cpp;subdir=${CLUSTER_DIR} \
      file://ActivatedEvent.h;subdir=${CLUSTER_DIR} \
      file://main.qml;subdir=${CLUSTER_DIR} \
      file://qml.qrc;subdir=${CLUSTER_DIR} \
      file://images/*;subdir=${CLUSTER_DIR} \
      file://qml/*;subdir=${CLUSTER_DIR} \
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
    install -m 0644 ${WORKDIR}/${CLUSTER_DIR}/cluster-view.service ${D}${systemd_system_unitdir}/cluster-view.service
}

