FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

require xen.inc

RDEPENDS_${PN}_remove_class-target = " ${PYTHON_PN}-core"
FILES:${PN} = "\
    ${libdir}/xen/bin/test-xenstore \
    ${libdir}/xen/bin/test-resource \
    ${libdir}/xen/bin/test-paging-mempool \
    ${sysconfdir}/xen/cpupool \
    ${sysconfdir}/xen/auto \
"

do_install_append() {
    rm -f ${D}/${libdir}/xen/bin/init-dom0less
    rm -f ${D}/${systemd_unitdir}/system/var-lib-xenstored.mount
    rm -rf ${D}/var
}

FILES_${PN}-xencommons_remove = "\
    "${systemd_unitdir}/system/var-lib-xenstored.mount" \
"

SYSTEMD_SERVICE_${PN}-xencommons_remove = " \
    var-lib-xenstored.mount \
"

# Remove the recommendation for Qemu for non-hvm x86 added in meta-virtualization layer
RRECOMMENDS_${PN}_remove = " qemu"
