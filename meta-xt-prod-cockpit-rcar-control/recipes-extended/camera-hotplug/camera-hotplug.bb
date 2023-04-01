SUMMARY = "Camera Hotplug"
LICENSE = "CLOSED"

SRC_URI = "file://camera-hotplug.service \
"

S = "${WORKDIR}"

inherit systemd

SYSTEMD_SERVICE_${PN} = "camera-hotplug.service"

FILES_${PN} += " \
    ${systemd_system_unitdir}/camera-hotplug.service \
"

do_install_append() {
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/camera-hotplug.service ${D}${systemd_system_unitdir}/camera-hotplug.service
}
