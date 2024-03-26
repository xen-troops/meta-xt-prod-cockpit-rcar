FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SUMMARY = "QT Cluster application"
LICENSE = "CLOSED"

CLUSTER_DIR="cluster-view-src"

SRC_URI = " \
      file://cluster_view_unit_tests/cluster_view_unit_tests.pro;subdir=${CLUSTER_DIR} \
      file://cluster_view_unit_tests/tst_cluster_view_input.cpp;subdir=${CLUSTER_DIR} \
      file://visclient.h;subdir=${CLUSTER_DIR} \
      file://visclient.cpp;subdir=${CLUSTER_DIR} \
      file://VisSocket.h;subdir=${CLUSTER_DIR} \
      file://VisSocket.cpp;subdir=${CLUSTER_DIR} \
      file://QtVisSocket.cpp;subdir=${CLUSTER_DIR} \
      file://QtVisSocket.h;subdir=${CLUSTER_DIR} \
      file://Consumers.cpp;subdir=${CLUSTER_DIR} \
      file://Consumers.h;subdir=${CLUSTER_DIR} \
"

DEPENDS += " \
     qtbase-native \
"

S = "${WORKDIR}/${CLUSTER_DIR}/cluster_view_unit_tests"

inherit native qmake5

do_install_append() {
         install -d ${D}${bindir}/unit-tests
         install -m 0755 cluster_view_unit_tests ${D}${bindir}/unit-tests
         install -d ${DEPLOY_DIR}/unit-tests
         install -m 0755 cluster_view_unit_tests ${DEPLOY_DIR}/unit-tests
}

