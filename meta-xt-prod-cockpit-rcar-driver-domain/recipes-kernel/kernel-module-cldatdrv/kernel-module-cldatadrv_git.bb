SUMMARY = "RCAR cluster data drive Module"
LICENSE = "CLOSED"

inherit module

PR = "r0"
PV = "0.1"

SRC_URI = "git://github.com/iusyk/cluster_data_drv.git;ptotocol=http;branch=master"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

DEPENDS += " \
    glibc \
"
# Auto load rcar_cluster_drv
KERNEL_MODULE_AUTOLOAD_append = " rcar_cluster_drv"

#export KERNELSRC = "${STAGING_KERNEL_DIR}"
# Ship the module symbol file to kernel build dir
SYSROOT_PREPROCESS_FUNCS = "module_sysroot_symbol"

FILES_${PN} = " \
    /lib/modules/${KERNEL_VERSION}/extra/rcar_cluster_drv.ko \
    ${sysconfdir}/modules-load.d \
"

EXTRA_OEMAKE = "KERNEL_SRC=${STAGING_KERNEL_BUILDDIR}"
EXTRA_OEMAKE += "CROSS_COMPILE=${CROSS_COMPILE}"

KERNEL_MODULE_PACKAGE_SUFFIX = ""

# Clean up the module symbol file
CLEANFUNCS = "module_clean_symbol"

RPROVIDES_${PN} += "kernel-module-rcar-cluster-drv"

module_clean_symbol() {
    rm -f ${S}/Module.symvers
}

module_sysroot_symbol() {
    install -m 644 ${S}/Module.symvers ${STAGING_KERNEL_BUILDDIR}/rcar_cluster_drv.symvers
}

module_do_install () {
    install -d ${D}/lib/modules/${KERNEL_VERSION}/extra/
    install -d ${D}${includedir}

    install -m 644 ${S}/r_taurus_cluster_protocol.h ${D}${includedir}
    # Install kernel module
    install -m 644 ${S}/rcar_cluster_drv.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/
    # Install shared library to KERNELSRC(STAGING_KERNEL_DIR) for reference from other modules
    # This file installed in SDK by kernel-devsrc pkg.
    install -m 644 ${S}/Module.symvers ${STAGING_KERNEL_DIR}/include/rcar_cluster_drv.symvers
}
