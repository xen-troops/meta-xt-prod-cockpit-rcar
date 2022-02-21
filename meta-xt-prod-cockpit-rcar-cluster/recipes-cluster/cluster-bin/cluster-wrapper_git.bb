
SUMMARY = "Compilation of cluster_wrapper.bin to flash cr7"
DESCRIPTION = "build of cluster_bin"

LICENSE = "CLOSED"

SRC_URI = " \
   git://git@gitpct.epam.com/epmd-aepr/vlib;protocol=ssh;branch=vlib-root \
"

SRCREV = "${AUTOREV}"

DEPENDS = " \
   gcc-arm-none-eabi-native \
"
do_compile() {
    make -C "${WORKDIR}/git/app/cluster_wrapper/target/arm-gnu-freertos_cr7_r-carx3"
}

do_install() {
    install -d ${DEPLOY_DIR}
    install -m 0644 ${WORKDIR}/git/app/cluster_wrapper/target/arm-gnu-freertos_cr7_r-carx3/cluster_wrapper.bin ${DEPLOY_DIR}/cluster_wrapper.bin
}

