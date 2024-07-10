require qt5-xt-git.inc

FILESEXTRAPATHS:prepend := "${THISDIR}/qtdeclarative:"

SRC_URI:append = " \ 
    file://0001-yarr-Include-limits-for-numeric_limits.patch \ 
    file://0001-qmldebug-Include-limits-header.patch \
"
# keep value empty
LDFLAGS:remove:riscv64 = "-pthread"

EXTRA_QMAKEVARS_CONFIGURE:remove = "${PACKAGECONFIG_CONFARGS}"

do_install_ptest() {
   ;
}

SRCREV = "02c499996bc70eae5472a0290ca09f1f1741e5cb"
