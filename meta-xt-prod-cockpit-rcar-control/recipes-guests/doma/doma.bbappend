FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

RDEPENDS:${PN} += "backend-ready"

SRC_URI += "\
    file://doma-vdevices.cfg \
    file://doma-set-root \
    file://doma-set-root.conf \
    file://doma-pvcamera.conf \
    file://doma-pvcamera.cfg \
"

FILES:${PN} += " \
    ${libdir}/xen/bin/doma-set-root \
    ${sysconfdir}/systemd/system/doma.service.d/doma-set-root.conf \
    ${@bb.utils.contains('DISTRO_FEATURES', 'pvcamera', '${sysconfdir}/systemd/system/doma.service.d/doma-pvcamera.conf', '', d)} \
"

RDEPENDS:${PN}:remove = "u-boot-android-bazel"
RDEPENDS:${PN}:append = " u-boot-android"

do_install:append() {
    cat ${WORKDIR}/doma-vdevices.cfg >> ${D}${sysconfdir}/xen/doma.cfg

    # Install doma-set-root script and the drop-in file to run it
    install -d ${D}${libdir}/xen/bin
    install -m 0744 ${WORKDIR}/doma-set-root ${D}${libdir}/xen/bin

    install -d ${D}${sysconfdir}/systemd/system/doma.service.d
    install -m 0644 ${WORKDIR}/doma-set-root.conf ${D}${sysconfdir}/systemd/system/doma.service.d

    if ${@bb.utils.contains('DISTRO_FEATURES', 'pvcamera', 'true', 'false', d)}; then
        cat ${WORKDIR}/doma-pvcamera.cfg >> ${D}${sysconfdir}/xen/doma.cfg
        install -m 0644 ${WORKDIR}/doma-pvcamera.conf ${D}${sysconfdir}/systemd/system/doma.service.d
    fi
}
