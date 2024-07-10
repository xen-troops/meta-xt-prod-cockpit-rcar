SUMMARY = ""
LICENSE = "CLOSED"

SRC_URI = " \
     file://dejavu-sfd-1.15.tar.gz;unpack=1 \
     file://dejavu-ttf-1.15.tar.gz;unpack=1 \
"

RDEPENDS:${PN} =+ "bash perl perl-modules"

do_install(){
     # Create the opt folder into the final image, ${D} is ${WORKDIR}/image
    install -d ${D}/${libdir}/fonts/
    # Copy the compressed file there; You can change permissions as you want
    install -m 0755 ${WORKDIR}/dejavu-sfd-1.15/* ${D}/${libdir}/fonts/
    install -m 0755 ${WORKDIR}/dejavu-ttf-1.15/* ${D}/${libdir}/fonts/
}

# Very important to specify what you installed in (do_install)
FILES:${PN} = " \
    ${libdir}/fonts/* \
"
