DESCRIPTION = "Toolchain to build cluster-wrapper"
LICENSE = "CLOSED"

inherit native

PV = "10-2020-q4-major"

SRC_URI = " \
    https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-${PV}-x86_64-linux.tar.bz2 \
"

INSANE_SKIP_${PN} = "already-stripped"
SRC_URI[sha256sum] = "21134caa478bbf5352e239fbc6e2da3038f8d2207e089efc96c3b55f1edcd618"
SRC_URI[md5sum] = "8312c4c91799885f222f663fc81f9a31"


FILES:${PN} = "${datadir} ${bindir}"

do_install() {

    install -d ${D}${datadir}/arm-none-eabi-${PV}/
    cp -r ${S}/../gcc-arm-none-eabi-${PV}/* ${D}${datadir}/

    install -d ${D}${bindir}
    # Symlink all executables into bindir
    for f in ${D}${datadir}/bin/arm-none-eabi-*; do
    	 ln --relative --symbolic $f ${D}${bindir}/$(basename $f)
    done
}

