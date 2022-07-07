SUMMARY = "Application generates the fs_data.c and Images.c for cluster application."
LICENSE = "CLOSED"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

inherit native

SRC_URI = "file://main.cpp"

S = "${WORKDIR}"

do_compile() {
         ${CXX} main.cpp -o fsgen
}

do_install() {
         install -d ${D}${bindir}
         install -m 0755 fsgen ${D}${bindir}
}
