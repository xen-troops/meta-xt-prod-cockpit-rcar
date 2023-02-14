require qt5-xt-git.inc

# keep value empty
LDFLAGS_remove_riscv64 = "-pthread"

EXTRA_QMAKEVARS_CONFIGURE_remove = "${PACKAGECONFIG_CONFARGS}"

do_install_ptest() {
   ;
}

SRCREV = "02c499996bc70eae5472a0290ca09f1f1741e5cb"
