
DEPENDS:append_toolchain-clang = " clang llvm-common"

SRCREV = "9e057a55368286058023510efc328f68250ecb5e"
PV = "4.12.0+git${SRCPV}"

SRC_URI:remove = " \
    git://code.qt.io/qt-creator/qt-creator.git;branch=4.15 \
    file://0001-app-Use-malloc_trim-only-on-glibc.patch \
"
SRC_URI = " \
    git://code.qt.io/qt-creator/qt-creator.git;branch=4.12 \
"

EXTRA_QMAKEVARS_PRE:remove = " \
    IDE_LIBRARY_BASENAME=${baselib}${QT_DIR_NAME} \
    CONFIG+=disable_external_rpath \
"

EXTRA_QMAKEVARS_PRE += "IDE_LIBRARY_BASENAME=${baselib}${QT_DIR_NAME}"

PACKAGECONFIG:remove:toolchain-clang = " clang"

# Important note: In case clang was added to qttools' PACKAGECONFIG, it has to
# be added here too - otherwise build fails trying to link native clang libraries
PACKAGECONFIG[clang] = ""

do_configure:append() {
    if [ -e ${B}/share/qtcreator/translations/Makefile ]; then
        sed -i 's:${STAGING_BINDIR}.*/lrelease:${OE_QMAKE_PATH_EXTERNAL_HOST_BINS}/lrelease:g' ${B}/share/qtcreator/translations/Makefile
        sed -i 's:${STAGING_BINDIR}.*/lupdate:${OE_QMAKE_PATH_EXTERNAL_HOST_BINS}/lupdate:g' ${B}/share/qtcreator/translations/Makefile
        sed -i 's:${STAGING_BINDIR}.*/xmlpatterns:${OE_QMAKE_PATH_EXTERNAL_HOST_BINS}/xmlpatterns:g' ${B}/share/qtcreator/translations/Makefile
        sed -i 's:${STAGING_BINDIR}.*/lconvert:${OE_QMAKE_PATH_EXTERNAL_HOST_BINS}/lconvert:g' ${B}/share/qtcreator/translations/Makefile
    fi
}

do_install() {
   oe_runmake install INSTALL_ROOT=${D}${prefix}
}

do_install:append:toolchain-clang () {
    # Remove RPATHs embedded in bins
    chrpath --delete ${D}${libdir}/qtcreator/plugins/libClang*
    chrpath --delete ${D}${libexecdir}/qtcreator/clang*
}

FILES:${PN}:remove = " \
    cmake \
    qtwebengine-dev \
    qtwebengine-mkspecs \
    qtwebengine-plugins \
    ${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'qtwebengine-qmlplugins', '', d)} \
"

python() {
   pass   
}
