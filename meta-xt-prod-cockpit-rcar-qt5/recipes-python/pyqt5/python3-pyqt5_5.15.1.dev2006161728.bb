SUMMARY = "Python Qt5 Bindings"
AUTHOR = "Phil Thomson @ riverbank.co.uk"

HOMEPAGE = "http://riverbankcomputing.co.uk"
SECTION = "devel/python"
LICENSE = "GPLv3"
LIC_FILES_CHKSUM = "\
    file://LICENSE;md5=d32239bcb673463ab874e80d47fae504 \
"

SRC_URI = "\
    https://www.riverbankcomputing.com/static/Downloads/PyQt5/PyQt5-${PV}.tar.gz \
"
SRC_URI[sha256sum] = "b29e4771be495018faef9687919395165da49d391c840c4d1a2592c1089ce592"

S = "${WORKDIR}/PyQt5-${PV}"

