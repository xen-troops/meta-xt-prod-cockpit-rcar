S = "${WORKDIR}/git"

SRC_URI = " git://github.com/renesas-rcar/capture.git;branch=rcar_gen4;protocol=https \
	file://0001-Proccess-an-image-in-case-of-DRM-as-well-out_fb-is-n.patch \
	file://0001-Change-default-camera-list.patch \
	file://0002-Add-support-for-LVDS-cameras.patch \
"

SRCREV = "${AUTOREV}"



DEPENDS = "libdrm"

inherit pkgconfig



do_populate_lic[noexec] = "1"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

