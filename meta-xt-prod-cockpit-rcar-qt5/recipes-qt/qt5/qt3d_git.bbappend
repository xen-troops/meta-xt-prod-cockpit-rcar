require qt5-xt-git.inc

SRC_URI_remove_riscv64 = " file://0001-renderers-opengl-Link-in-libatomic-on-riscv.patch"
SRC_URI_remove_riscv32 = " file://0001-renderers-opengl-Link-in-libatomic-on-riscv.patch"

SRCREV = "dc26105a3abe6fe420151fd3f1b228835d2088ed"
