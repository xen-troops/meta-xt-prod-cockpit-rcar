FILESEXTRAPATHS_prepend := "${THISDIR}/files:"


SRCREV = "${AUTOREV}"
LINUX_VERSION = "5.10.0"

SRC_URI_append = " \
    file://defconfig \
    file://xt_pass_drv.cfg \
    file://boot-options.dtsi;subdir=git/arch/${ARCH}/boot/dts/renesas \
    file://0001-PM-clk-make-PM-clock-layer-compatible-with-clocks-th.patch \
    file://0002-firmware-arm_scmi-Add-clock-management-to-the-SCMI-p.patch \
    file://0001-device-tree-Introduce-scmi-nodes-to-work-with-clocks.patch \
    file://0001-r8a77951-scmi.dtsi-change-the-start-memory-address.patch \
"

