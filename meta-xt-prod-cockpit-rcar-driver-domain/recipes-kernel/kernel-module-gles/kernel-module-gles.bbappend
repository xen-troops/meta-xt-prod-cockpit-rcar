LIC_FILES_CHKSUM = " \
    file://GPL-COPYING;md5=60422928ba677faaa13d6ab5f5baaa1e \
    file://MIT-COPYING;md5=8c2810fa6bfdc5ae5c15a0c1ade34054 \
"

SRC_URI:remove = "file://blacklist.conf"
SRC_URI:remove = "file://0001-fixing-implicit-conversion-in-GCC-11.2.patch"

KBUILD_OUTDIR:r8a7795 = "binary_r8a7795_linux_release/target_aarch64/kbuild/"
KBUILD_OUTDIR:r8a7796 = "binary_r8a7796_linux_release/target_aarch64/kbuild/"
KBUILD_OUTDIR:r8a77965 = "binary_r8a77965_linux_release/target_aarch64/kbuild/"
KBUILD_OUTDIR:r8a77990 = "binary_r8a7799_linux_release/target_aarch64/kbuild/"

module_do_install() {
    unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
    install -d ${D}/lib/modules/${KERNEL_VERSION}
    cd ${KBUILD_DIR}
    oe_runmake DISCIMAGE="${D}" install
}

FILES:${PN}:remove = " \
    ${sysconfdir}/modprobe.d/blacklist.conf \
"

# Auto load pvrsrvkm
KERNEL_MODULE_AUTOLOAD:append = " pvrsrvkm"
