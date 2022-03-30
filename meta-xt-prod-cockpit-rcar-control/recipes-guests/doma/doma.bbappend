FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

RDEPENDS_${PN} += "backend-ready"

SRC_URI += "\
    file://doma-vdevices.cfg \
    file://doma-set-root \
"

FILES_${PN} += " \
    ${libdir}/xen/bin/doma-set-root \
"

do_install_append() {
    cat ${WORKDIR}/doma-vdevices.cfg >> ${D}${sysconfdir}/xen/doma.cfg

    # Install doma-set-root script
    install -d ${D}${libdir}/xen/bin
    install -m 0744 ${WORKDIR}/doma-set-root ${D}${libdir}/xen/bin

    # Call doma-set-root script
    sed -i 's/backend-ready.*/domd.service/' ${D}${systemd_unitdir}/system/doma.service
    # remove the dependency on sndbe and display backend - sound belongs to android, 
    # display backend does not exists
    sed -r 's/backend-ready@sndbe.service//' ${D}${systemd_unitdir}/system/doma.service
    sed -r 's/backend-ready@displbe.service//' ${D}${systemd_unitdir}/system/doma.service
    echo "[Service]" >> ${D}${systemd_unitdir}/system/doma.service
    echo "ExecStartPre=${libdir}/xen/bin/doma-set-root" >> ${D}${systemd_unitdir}/system/doma.service
}
