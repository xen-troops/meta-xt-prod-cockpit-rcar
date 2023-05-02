
SUMMARY = "Compilation of cluster_wrapper.bin to flash cr7"
DESCRIPTION = "build of cluster_bin"

LICENSE = "CLOSED"

inherit deploy

PLATFORM = "rcar"

PARALLEL_MAKE = ""

SRC_URI = " \
   git://git@gitpct.epam.com/epmd-aepr/vlib;protocol=ssh;branch=${BRANCH} \
"

SRCREV = "${AUTOREV}"
BRANCH = "CES-2023"

DEPENDS = " \
    cluster-wrapper-toolchain-native \
"

do_compile() {
     oe_runmake -C "${WORKDIR}/git/app/cluster_wrapper/target/arm-gnu-freertos_cr7_r-carx3"
}

do_install() {
    install -d ${DEPLOY_DIR}
    install -m 0644 ${WORKDIR}/git/app/cluster_wrapper/target/arm-gnu-freertos_cr7_r-carx3/cluster_wrapper.bin ${DEPLOY_DIR}/cluster_wrapper.bin
}

