SUMMARY = "v4l2loopback-module"
DESCRIPTION = "Adds loopback v4l2 devices"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"
SRCBRANCH = "main"

inherit module

SRC_URI = "git://github.com/umlaeute/v4l2loopback.git;protocol=https;branch=${SRCBRANCH} \
	file://0001-makefile-Adapt-makefile-for-yocto-build.patch \
"
SRCREV = "1ecf810f0d687b647caa3050ae30cf51b5902afd"

S = "${WORKDIR}/git"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

EXTRA_OEMAKE += "-I${S}/usr/bin "
FILESEXTRAPATHS_append := "${THISDIR}/files:"

RPROVIDES_${PN} += "kernel-module-v4l2loopback"
