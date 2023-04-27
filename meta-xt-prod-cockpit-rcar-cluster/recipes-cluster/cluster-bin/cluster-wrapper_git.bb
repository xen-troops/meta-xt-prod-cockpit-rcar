FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SUMMARY = "Compilation of cluster_wrapper.bin to flash cr7"
DESCRIPTION = "build of cluster_bin"

LICENSE = "CLOSED"

inherit deploy

PLATFORM = "rcar"

PARALLEL_MAKE = ""

SRC_URI = " \
   git://git@gitpct.epam.com/epmd-aepr/vlib;protocol=ssh;branch=CES-2023 \
   file://rescale.sh \
   file://rescaling_info_hdmi_1280_720;subdir=${WORKDIR}/git/app/2d-wow-cluster-demo/src/image \
   file://rescaling_info_lvds_1920_720;subdir=${WORKDIR}/git/app/2d-wow-cluster-demo/src/image \
"

SRCREV = "${AUTOREV}"

DEPENDS = " \
    fsdata-native \
    cluster-wrapper-toolchain-native \
"

S="${WORKDIR}/git"

do_compile() {
     if [ ! -f "${WORKDIR}/git/app/2d-wow-cluster-demo/src/image/rescaling_info_${CLUSTER_DISPL_MODE}" ]; then
         bbfatal "File ${WORKDIR}/git/app/2d-wow-cluster-demo/src/image/rescaling_info_${CLUSTER_DISPL_MODE} does not exist."
     fi

     ${WORKDIR}/rescale.sh rescaling_info_${CLUSTER_DISPL_MODE}
     oe_runmake PRIM_DISP_DU=1 CLUSTER_DU=1 -C "${WORKDIR}/git/app/cluster_wrapper/target/arm-gnu-freertos_cr7_r-carx3"
}

do_install() {
    install -d ${DEPLOY_DIR}
    install -m 0644 ${WORKDIR}/git/app/cluster_wrapper/target/arm-gnu-freertos_cr7_r-carx3/cluster_wrapper.bin ${DEPLOY_DIR}/cluster_wrapper.bin
}

