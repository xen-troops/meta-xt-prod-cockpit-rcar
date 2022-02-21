require qt5-xt-git.inc

SRC_URI_remove = " \
    file://0001-yarr-Include-limits-for-numeric_limits.patch \
    file://0001-qmldebug-Include-limits-header.patch \
"
# keep value empty
LDFLAGS_remove_riscv64 = "-pthread"

EXTRA_QMAKEVARS_CONFIGURE_remove = "${PACKAGECONFIG_CONFARGS}"

do_install_ptest() {
   ;
}

SRCREV = "02c499996bc70eae5472a0290ca09f1f1741e5cb"
