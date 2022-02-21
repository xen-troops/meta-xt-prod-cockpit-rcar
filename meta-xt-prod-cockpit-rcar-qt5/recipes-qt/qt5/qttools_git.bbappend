require qt5-xt-git.inc

SRC_URI_remove_class-native = " \
     ${@bb.utils.contains('PACKAGECONFIG', 'clang', 'file://0004-Force-native-build-of-qt-help-tools-as-qhelpgenerato.patch', '', d)} \
"


TOOLSTOBUILD += "linguist/lconvert linguist/lrelease linguist/lupdate pixeltool qtdiag qtpaths qtplugininfo"
TOOLSTOBUILD += "${@bb.utils.contains('PACKAGECONFIG', 'clang', 'qdoc', '', d)}"
TOOLSFORTARGET = "pixeltool qtdiag qtpaths qtplugininfo"
TOOLSFORHOST = "linguist ${@bb.utils.contains('PACKAGECONFIG', 'clang', 'qdoc', '', d)}"

EXTRA_QMAKEVARS_PRE_remove = " \
     ${@bb.utils.contains('PACKAGECONFIG', 'clang', 'CONFIG+=disable_external_rpath CONFIG+=assistant', 'CONFIG+=noqdoc', d)} \
"

EXTRA_QMAKEVARS_PRE_append_class-native = " CONFIG+=config_clang_done CONFIG-=config_clang"
EXTRA_QMAKEVARS_PRE_append_class-nativesdk = " CONFIG+=config_clang_done CONFIG-=config_clang"
EXTRA_QMAKEVARS_PRE_append_class-target = "\
    ${@bb.utils.contains('PACKAGECONFIG', 'clang', 'CONFIG+=config_clang', 'CONFIG+=config_clang_done CONFIG-=config_clang', d)} \
"
SRCREV = "72744ac361a94bfd80af16403a69f8ff2422d583"

