S = "${WORKDIR}/git"

SRC_URI = " git://github.com/renesas-rcar/capture.git;branch=rcar_gen4;protocol=https \
	file://0001-Proccess-an-image-in-case-of-DRM-as-well-out_fb-is-n.patch \
	file://0001-Change-default-camera-list.patch \
	file://0002-Add-support-for-LVDS-cameras.patch \
"

SRCREV = "3a5d7b2695c6a8f00efb58e7a63850480acc603a"

DEPENDS = "libdrm"

inherit pkgconfig

do_populate_lic[noexec] = "1"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
