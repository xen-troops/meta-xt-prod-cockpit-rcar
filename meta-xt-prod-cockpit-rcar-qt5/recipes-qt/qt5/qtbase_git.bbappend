
require qt5-xt-git.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/qtbase:"

SRC_URI_remove = " \
    file://0001-Add-linux-oe-g-platform.patch \
    file://0008-Replace-pthread_yield-with-sched_yield.patch \
    file://0004-configure-bump-path-length-from-256-to-512-character.patch \
    file://0018-tst_qpainter-FE_-macros-are-not-defined-for-every-pl.patch \
    file://0019-Define-__NR_futex-if-it-does-not-exist.patch \
    file://0020-Revert-Fix-workaround-in-pthread-destructor.patch \
"

SRC_URI_append = " \
    file://0001-Add-linux-oe-g-platform-xt.patch \
    file://0008-Replace-pthread_yield-with-sched_yield-xt.patch \
    file://0004-configure-bump-path-length-from-256-to-512-character-xt.patch \
    file://0018-tst_qpainter-FE_-macros-are-not-defined-for-every-pl-xt.patch \
"

unset LTO

LDFLAGS_remove_riscv64 = "-pthread"

SRCREV = "e4961b35deb202525d4711dbb14f8c2bb0bf5c26"

PACKAGECONFIG_GL = "${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'gles2 eglfs', 'no-opengl', d)}"

PACKAGECONFIG += "eglfs gl gles2 linuxfb kms libinput"
PACKAGECONFIG[vsp2] = "-feature-vsp2,-no-feature-vsp2,v4l-utils,libv4l"
PACKAGECONFIG += "vsp2"
PACKAGECONFIG[gbm] = "-gbm,-no-gbm,libgbm"
PACKAGECONFIG += "gbm"

PACKAGECONFIG_remove += " pcre"

do_install_append() {
    # Update the mkspecs to include the default OE toolchain config for the target
    conf=${D}/${OE_QMAKE_PATH_QT_ARCHDATA}/mkspecs/${XPLATFORM}/qmake.conf
    cat /dev/null > $conf

    echo "" >> $conf
    echo "#" >> $conf
    echo "# qmake configuration for linux-g++ with modifications for building with OpenEmbedded" >> $conf
    echo "#" >> $conf

    echo "MAKEFILE_GENERATOR = UNIX" >> $conf
    echo "CONFIG += incremental" >> $conf
    echo "QMAKE_INCREMENTAL_STYLE = sublib" >> $conf

    echo "include(../common/linux.conf)" >> $conf

    echo "# QMAKE_<TOOL> (moc, uic, rcc) are gone, overwrite only ar and strip" >> $conf
    echo "QMAKE_AR              = \$\$(OE_QMAKE_AR) cqs" >> $conf
    echo "QMAKE_STRIP           = \$\$(OE_QMAKE_STRIP)" >> $conf

    echo "include(../common/gcc-base-unix.conf)" >> $conf

    echo "# *FLAGS from gcc-base.conf" >> $conf
    echo "QMAKE_CFLAGS                += \$\$(OE_QMAKE_CFLAGS)" >> $conf
    echo "QMAKE_CXXFLAGS              += \$\$(OE_QMAKE_CXXFLAGS)" >> $conf
    echo "QMAKE_LFLAGS                += \$\$(OE_QMAKE_LDFLAGS)" >> $conf

    echo "include(../common/g++-unix.conf)" >> $conf

    echo "# tc settings from g++-base.conf" >> $conf
    echo "QMAKE_CC       = \$\$(OE_QMAKE_CC)" >> $conf
    echo "QMAKE_CXX      = \$\$(OE_QMAKE_CXX)" >> $conf

    echo "QMAKE_LINK         = \$\$(OE_QMAKE_LINK)" >> $conf
    echo "QMAKE_LINK_SHLIB   = \$\$(OE_QMAKE_LINK)" >> $conf
    echo "QMAKE_LINK_C       = \$\$(OE_QMAKE_LINK)" >> $conf
    echo "QMAKE_LINK_C_SHLIB = \$\$(OE_QMAKE_LINK)" >> $conf
    echo "QMAKE_CFLAGS_ISYSTEM =" >> $conf
    echo "# for the SDK" >> $conf
    echo "isEmpty(QMAKE_QT_CONFIG):QMAKE_QT_CONFIG = \$\$(OE_QMAKE_QT_CONFIG)" >> $conf

    echo "include(../oe-device-extra.pri)" >> $conf

    echo "load(device_config)" >> $conf
    echo "load(qt_config)" >> $conf

    echo "# default compiler options which can be overwritten from the environment" >> $conf
    echo "isEmpty(QMAKE_AR): QMAKE_AR = ${OE_QMAKE_AR} cqs" >> $conf
    echo "isEmpty(QMAKE_CC): QMAKE_CC = $OE_QMAKE_CC_NO_SYSROOT" >> $conf
    echo "isEmpty(QMAKE_CFLAGS): QMAKE_CFLAGS = ${OE_QMAKE_CFLAGS}" >> $conf
    echo "isEmpty(QMAKE_CXX): QMAKE_CXX = $OE_QMAKE_CXX_NO_SYSROOT" >> $conf
    echo "isEmpty(QMAKE_CXXFLAGS): QMAKE_CXXFLAGS = ${OE_QMAKE_CXXFLAGS}" >> $conf
    echo "isEmpty(QMAKE_LINK): QMAKE_LINK = $OE_QMAKE_LINK_NO_SYSROOT" >> $conf
    echo "isEmpty(QMAKE_LINK_SHLIB): QMAKE_LINK_SHLIB = $OE_QMAKE_LINK_NO_SYSROOT" >> $conf
    echo "isEmpty(QMAKE_LINK_C): QMAKE_LINK_C = $OE_QMAKE_LINK_NO_SYSROOT" >> $conf
    echo "isEmpty(QMAKE_LINK_C_SHLIB): QMAKE_LINK_C_SHLIB = $OE_QMAKE_LINK_NO_SYSROOT" >> $conf
    echo "isEmpty(QMAKE_LFLAGS): QMAKE_LFLAGS = ${OE_QMAKE_LDFLAGS}" >> $conf
    echo "isEmpty(QMAKE_STRIP): QMAKE_STRIP = ${TARGET_PREFIX}strip" >> $conf
    echo "isEmpty(CC_host): CC_host = ${CC_host}" >> $conf
    echo "isEmpty(CXX_host): CXX_host = ${CXX_host}" >> $conf
    echo "isEmpty(LD_host): LD_host = ${LD_host}" >> $conf
}
