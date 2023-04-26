SUMMARY = "Application generates the fs_data.c and Images.c for cluster application."
LICENSE = "CLOSED"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

inherit native

SRC_URI = "file://main.cpp"

S = "${WORKDIR}"

do_compile() {
         ${CXX} -std=c++17 main.cpp -o cr7-image-gen
}

do_install() {
         install -d ${D}${bindir}
         install -m 0755 cr7-image-gen ${D}${bindir}
}
