FILESEXTRAPATHS_prepend := "${THISDIR}/files:"


SRCREV = "${AUTOREV}"
LINUX_VERSION = "5.10.0"

SRC_URI_append = " \
    file://defconfig \
    file://xt_pass_drv.cfg \
    file://boot-options.dtsi;subdir=git/arch/${ARCH}/boot/dts/renesas \
    file://0001-OF-DT-Overlay-configfs-interface-v7.patch \
    file://0002-of-overlay-kobjectify-overlay-objects.patch \
    file://0003-of-overlay-global-sysfs-enable-attribute.patch \
    file://0004-Documentation-ABI-overlays-global-attributes.patch \
    file://0005-Documentation-document-of_overlay_disable-parameter.patch \
    file://0006-of-overlay-add-per-overlay-sysfs-attributes.patch \
    file://0007-Documentation-ABI-overlays-per-overlay-docs.patch \
    file://0008-of-rename-_node_sysfs-to-_node_post.patch \
"

